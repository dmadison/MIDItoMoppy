/*
 *  Project     MIDI-to-Moppy Library
 *  @author     David Madison
 *  @link       github.com/dmadison/MIDItoMoppy
 *  @license    MIT - Copyright (c) 2017 David Madison
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "MIDItoMoppy.h"

MIDItoMoppy::MIDItoMoppy(){
	setResolution(DefaultResolution);
}

MIDItoMoppy::MIDItoMoppy(uint16_t resolution){
	setResolution(resolution);
}

MIDItoMoppy::MIDItoMoppy(Stream &port) : SerialPort(&port){
	setResolution(DefaultResolution);
}

MIDItoMoppy::MIDItoMoppy(Stream &port, uint16_t resolution) : SerialPort(&port){
	setResolution(resolution);
}

void MIDItoMoppy::setResolution(uint16_t resolution){
	if(resolution == 0){ resolution = DefaultResolution; }

	arduinoResolution = resolution * 2; // Dobuled because pin is toggled, not stepped

	for(uint8_t i = 0; i < NoteRange; i++){
		moppyNotes[i] = (pgm_read_word_near(MicroPeriods + i) / arduinoResolution);
	}
}

uint16_t MIDItoMoppy::getResolution(){
	return arduinoResolution / 2;
}

uint16_t MIDItoMoppy::getPeriod(uint8_t note){
	if(!checkRange(note)){
		return 0;
	}

	// MicroPeriods index shiftered - 24 because C1 starts at MIDI note 24 (array index 0)
	return (moppyNotes[note - NoteOffset]);
}

static uint16_t MIDItoMoppy::getPeriod(uint8_t note, uint16_t resolution){
	if(!checkRange(note) || resolution == 0){
		return 0;
	}

	// MicroPeriods index is shiftered '- 24' because C1 starts at MIDI note 24 (array index 0)
	// Resolution is doubled because pin is toggled, not stepped
	return (pgm_read_word_near(MicroPeriods + (note - NoteOffset)) / (resolution * 2));
}

static int8_t MIDItoMoppy::getPin(uint8_t channel){
	if(!checkChannel(channel)){
		return -1; // No valid drive
	}

	return (channel * 2); // Stepper pin is double the channel number
}

static boolean MIDItoMoppy::checkChannel(uint8_t channel){
	// Channels 1 - 16 (MIDI notation)
	// Max channel is 9 (Arduino Uno)
	if(channel == 0 || channel > 9){
		return false;
	}

	return true;
}

static boolean MIDItoMoppy::checkRange(uint8_t note){
	if(note < NoteOffset || note >= (NoteOffset + NoteRange)){
		return false;
	}

	return true;
}

static boolean MIDItoMoppy::checkInputs(uint8_t channel, uint8_t note){
	if(checkChannel(channel) && checkRange(note)){
		return true;
	}

	return false;
}

static boolean MIDItoMoppy::checkMIDIChannel(uint8_t channel){
	if(channel == 0 || channel > 16){
		return false;
	}

	return true;
}

static boolean MIDItoMoppy::checkMIDIRange(uint8_t note){
	if(note > 127){
		return false;
	}

	return true;
}

static boolean MIDItoMoppy::checkMIDIInputs(uint8_t channel, uint8_t note){
	if(checkMIDIChannel(channel) && checkMIDIRange(note)){
		return true;
	}

	return false;
}

static void MIDItoMoppy::sendMoppy(Stream &port, uint8_t pin, uint16_t period){
	port.write(pin);
	port.write(period >> 8 & 0xFF);
	port.write(period & 0xFF);
}

void MIDItoMoppy::sendMoppy(uint8_t pin, uint16_t period){
	if(!SerialPort){ return; }
	sendMoppy(*SerialPort, pin, period);
}

void MIDItoMoppy::sendNoteOn(uint8_t channel, uint8_t note){
	if(!SerialPort){ return; }

	int8_t pin = getPin(channel);
	if(pin < 0){ return; }

	uint16_t period = getPeriod(note);
	if(period == 0){ return; }

	sendMoppy(*SerialPort, pin, period);
}

void MIDItoMoppy::sendNoteOff(uint8_t channel, uint8_t note){
	if(!SerialPort){ return; }

	sendNoteOff(*SerialPort, channel, note);
}

static void MIDItoMoppy::sendNoteOn(Stream &port, uint8_t channel, uint8_t note){
	int8_t pin = getPin(channel);
	if(pin < 0){ return; }

	uint16_t period = getPeriod(note, DefaultResolution);
	if(period == 0){ return; }

	sendMoppy(port, pin, period);
}

static void MIDItoMoppy::sendNoteOff(Stream &port, uint8_t channel, uint8_t note){
	int8_t pin = getPin(channel);
	if(pin < 0){ return; }

	if(!checkRange(note)){ return; }

	sendMoppy(port, pin, 0);
}


void MIDItoMoppy::resetResolution(){
	setResolution(DefaultResolution);
}

void MIDItoMoppy::reset(){
	resetResolution();
}

