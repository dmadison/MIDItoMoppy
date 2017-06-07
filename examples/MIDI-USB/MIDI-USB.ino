/* 
 * MIDI-USB Example for MIDI-to-Moppy Library
 * by David Madison
 * 
 * Acts as a native MIDI USB device and relays MIDI messages over a hardware
 * serial port to the Moppy controller. Only works with Arduinos that have
 * native USB support (e.g. Leonardo, Pro Micro).
 * 
 * This example requires the Arduino MIDIUSB library, which you can
 * download at https://github.com/arduino-libraries/MIDIUSB
 * 
 */

#include <MIDItoMoppy.h>
#include <MIDIUSB.h>

MIDItoMoppy Moppy(Serial1); // Send messages to Moppy from the second serial line

void setup() {
	Serial1.begin(9600); // Baud rate of Moppy
}

void loop() {
	midiEventPacket_t rx = MidiUSB.read();

	// Only process if data is available
	if(rx.header != 0){
		uint8_t mode     =  rx.byte1 & 0xF0;      // First nybble is the MIDI mode
		uint8_t channel  = (rx.byte1 & 0x0F) + 1; // Second nybble is the MIDI channel. +1 for MIDI notation (1 - 16)
		uint8_t note     =  rx.byte2;

		// Note On
		if(mode == 0x90){
			Moppy.sendNoteOn(channel, note);
		}
		// Note Off
		else if(mode == 0x80){
			Moppy.sendNoteOff(channel, note);
		}
	}
}
