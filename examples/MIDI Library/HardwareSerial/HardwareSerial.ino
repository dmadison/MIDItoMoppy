/* 
 * HardwareSerial Example for MIDI-to-Moppy Library
 * by David Madison
 * 
 * Relays MIDI messages from serial over a second hardware port to the
 * Moppy controller. Only works with Arduinos that have two hardware
 * serial ports (Leonardo, Mega, etc.). 
 * 
 * This example requires the Arduino MIDI library, which you can
 * download at https://github.com/fortySevenEffects/arduino_midi_library/
 * 
 */
 
#include <MIDItoMoppy.h>
#include <MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE();

MIDItoMoppy Moppy(Serial1); // Send messages to Moppy from the second serial line

void setup(){ 
	MIDI.setHandleNoteOn(handleNoteOn);
	MIDI.setHandleNoteOff(handleNoteOff);

	Serial1.begin(9600); // Baud rate of Moppy
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
