/* 
 * SoftwareSerial Example for MIDI-to-Moppy Library
 * by David Madison
 * 
 * Relays MIDI messages from serial over a software serial port to the
 * Moppy controller.
 * 
 * This example requires both Arduino MIDI library, which you can
 * download at https://github.com/fortySevenEffects/arduino_midi_library/,
 * and the SoftwareSerial library, which is included with versions of the
 * Arduino IDE newer than 1.0.
 * 
 */
 
#include <MIDItoMoppy.h>
#include <MIDI.h>
#include <SoftwareSerial.h>

MIDI_CREATE_DEFAULT_INSTANCE();
SoftwareSerial mySerial(10, 11); // RX, TX

MIDItoMoppy Moppy(mySerial); // Send messages to Moppy from the software serial port

void setup(){ 
	MIDI.setHandleNoteOn(handleNoteOn);
	MIDI.setHandleNoteOff(handleNoteOff);

	mySerial.begin(9600); // Baud rate of Moppy
	MIDI.begin(MIDI_CHANNEL_OMNI); // Listen on all MIDI channels
}
 
void loop(){
	MIDI.read(); // Check for MIDI messages every loop
}

void handleNoteOn(byte channel, byte note, byte velocity){
	Moppy.sendNoteOn(channel, note);
}
 
void handleNoteOff(byte channel, byte note, byte velocity){
	Moppy.sendNoteOff(channel, note);
}
