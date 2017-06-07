/* 
 * PrintRandom Example for MIDI-to-Moppy Library
 * by David Madison
 * 
 * Generates a random MIDI note, channel, and velocity to be transposed.
 * The MIDI message and Moppy message are printed over serial.
 * 
 */

#include <MIDItoMoppy.h>

MIDItoMoppy Moppy; // Default instance with a resolution of 40 microseconds

void setup() {
	Serial.begin(9600);
}

void loop() {  
	uint8_t channel = random(1, 17);  // Random MIDI channel from 1 - 16
	uint8_t note    = random(0, 128); // Random MIDI note from 0 - 127
	// uint8_t velocity = random(0, 128); <- Velocity is not used for floppy drives!

	// Print the current MIDI message
	Serial.print("MIDI  Message: ");
	Serial.print("Ch: ");
	Serial.print(channel);
	Serial.print(" Note: ");
	Serial.print(note);
	Serial.println();

	// Print the transposed Moppy message
	Serial.print("Moppy Message: ");
	Serial.print("Pin: ");
	Serial.print(Moppy.getPin(channel)); // Prints "-1" if channel is out of range (1 - 9)
	Serial.print(" Period: ");
	Serial.print(Moppy.getPeriod(note)); // Prints "0" if note is out of range (24 - 71)
	Serial.println();

	Serial.println();
	delay(2000);
}


