/* 
 * PrintAll Example for MIDI-to-Moppy Library
 * by David Madison
 * 
 * Prints the corresponding stepper pin for each channel and the microsecond periods
 * for MIDI notes 0 - 127, at both the default resolution of 40 and a custom resolution
 * of 20 microseconds.
 * 
 */

#include <MIDItoMoppy.h>

MIDItoMoppy Moppy; // Default instance with a resolution of 40 microseconds

void setup() {
	Serial.begin(9600);

	Serial.println("Moppy Stepper Pins:");
	printPins();

	Serial.print("Moppy Default Resolution: ");
	Serial.println(Moppy.getResolution());
	printNotes();

	Moppy.setResolution(20);
	Serial.print("Moppy Custom Resolution: ");
	Serial.println(Moppy.getResolution());
	printNotes();
}

// Print the corresponding stepper pins for channels 1 - 16
// Out of range values print "-1"
void printPins(){
	for(int i = 1; i <= 16; i++){
		Serial.print("Ch #: ");
		Serial.print(i);
		Serial.print(" - ");

		Serial.println(Moppy.getPin(i));
	}
	Serial.println();
}

// Print the period values for notes 0 - 127
// Out of range values print "0"
void printNotes(){
	for(int i = 0; i <= 127; i++){
		Serial.print("Note #: ");
		Serial.print(i);
		Serial.print(" - ");

		Serial.println(Moppy.getPeriod(i));
	}
	Serial.println();
}

void loop() {
  // put your main code here, to run repeatedly:
}
