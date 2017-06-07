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

#ifndef MIDItoMoppy_h
#define MIDItoMoppy_h

#include <Arduino.h>
#include <avr/pgmspace.h>

#include "MusicalPeriods.h"

class MIDItoMoppy{
	public:
		MIDItoMoppy();
		MIDItoMoppy(uint16_t resolution);
		MIDItoMoppy(Stream &port);
		MIDItoMoppy(Stream &port, uint16_t resolution);

		void
			setResolution(uint16_t resolution);
		uint16_t
			getResolution();

		uint16_t 
			getPeriod(uint8_t note);
		static uint16_t
			getPeriod(uint8_t note, uint16_t resolution);

		static int8_t
			getPin(uint8_t channel);

		static boolean 
			checkChannel(uint8_t channel),
			checkRange  (uint8_t note),
			checkInputs (uint8_t channel, uint8_t note),

			checkMIDIChannel(uint8_t channel),
			checkMIDIRange  (uint8_t note),
			checkMIDIInputs (uint8_t channel, uint8_t note);

		void
			sendMoppy  (uint8_t pin, uint16_t period),
			sendNoteOn (uint8_t channel, uint8_t note),
			sendNoteOff(uint8_t channel, uint8_t note);

		static void
			sendMoppy  (Stream &port, uint8_t pin, uint16_t period),
			sendNoteOn (Stream &port, uint8_t channel, uint8_t note),
			sendNoteOff(Stream &port, uint8_t channel, uint8_t note);

		void
			resetResolution(),
			reset();

	private:
		static const uint8_t DefaultResolution = 40;
		static const uint8_t NoteRange = 48;
		static const int8_t  NoteOffset = 24;

		Stream * SerialPort;
		uint16_t moppyNotes[NoteRange];
		uint16_t arduinoResolution = DefaultResolution * 2;
};

#endif

