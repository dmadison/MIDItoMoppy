/* 
 * MoppySim Example for MIDI-to-Moppy Library
 * by David Madison
 * 
 * Code that simulates the serial reading functions of Moppy. Useful
 * for debugging MIDI-to-Moppy if you don't have floppy drives set up.
 * 
 * Connect the serial 'TX' pin on the MIDI-to-Moppy board to the RX
 * pin on the MoppySim board. Reconstructed messages are printed to
 * the serial monitor.
 * 
 */

void setup() {
	Serial.begin(9600); // Baud rate for Moppy
}
 
void loop() {
	if(Serial.available() >= 3){
		uint8_t pin = Serial.read();
		uint16_t period = Serial.read() << 8 | Serial.read();

		Serial.print("Pin: ");
		Serial.print(pin);
		Serial.print(" Period: ");
		Serial.print(period);
		Serial.println();
	}
}
