/* 
 * BlinkTone Example for MIDI-to-Moppy Library
 * by David Madison
 * 
 * Example that plays middle C, waits one second, stops it, and then repeats.
 * 
 * Connect the serial 'TX' pin on the MIDI-to-Moppy board to the RX
 * pin on the Moppy controller.
 * 
 */

#include <MIDItoMoppy.h>

MIDItoMoppy Moppy(Serial); // Default instance with a resolution of 40 microseconds

void setup() {
	Serial.begin(9600); // Moppy baud rate
}

void loop() {
	Moppy.sendNoteOn(1, 60); // Middle C (note 60) on Channel 1
	delay(1000);
	Moppy.sendNoteOff(1, 60);
	delay(1000);  
}
