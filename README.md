# MIDI-to-Moppy Library

This library converts MIDI data into the pin numbers and microsecond periods used by musical floppy drives being controlled by [Moppy](https://github.com/SammyIAm/Moppy/). This enables you to control a musical floppy drive setup without MoppyDesk or a PC.

*Note: This library is a work in progress! Functionally may change as it is developed.*

## Contents
- [Installation](#installation)
- [Getting Started](#getting-started)
- [Basic Functions](#basic-functions)
- [Advanced Functions](#advanced-functions)
- [Credits](#credits)
- [License](#license)

## Installation

1. Click "Clone or Download" in the upper-right to download this repository as a ZIP file.
2. Extract the contents of the ZIP file into your Arduino libraries folder.
3. Open the IDE and check out the examples under `File -> Examples -> MIDI-to-Moppy`.

## Getting Started

	MIDItoMoppy Moppy;
	MIDItoMoppy Moppy(40);
	MIDItoMoppy Moppy(Serial1);
	MIDItoMoppy Moppy(Serial1, 40);

Create an instance of the class. The constructor can take two arguments: serial port and interrupt resolution.

The serial port is the port that Moppy commands are sent across, *not* the one you're receiving MIDI messages from. It can be either a hardware or a software port. Be sure to connect the TX pin of this port to the RX pin of the microcontroller running Moppy.

By default the Moppy code uses a resolution of 40 microseconds. If you haven't modified the Moppy code, leave this setting alone.

## Basic Functions

	void sendNoteOn(uint8_t channel, uint8_t note);
	void sendNoteOff(uint8_t channel, uint8_t note);

Both of these functions take a MIDI channel (1 - 9) and a MIDI note (24 - 71 inclusive, or C<sub>1</sub> through C<sub>4</sub>), and sends the resultant stepper pin number and microsecond period to the Moppy controller. With the default settings, these are all you need to control the floppy drives!

The MIDI-to-Moppy library does not contain any functions to read MIDI, but it works well in combination with the [Arduino MIDI Library](https://github.com/FortySevenEffects/arduino_midi_library/):

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

I would recommend using an Arduino with two hardware serial ports (Leonardo, Pro Micro, Mega), although MIDI-to-Moppy also works with software serial. By default Moppy runs at a baud rate of 9600.

## Advanced Functions

All of the lower level functions are exposed if you'd like more control over the data stream.

### Lookup Functions

	       uint16_t getPeriod(uint8_t note);
	static uint16_t getPeriod(uint8_t note, uint16_t resolution);
	static   int8_t getPin(uint8_t channel);

Both of the `getPeriod` functions return a microperiod value for the corresponding MIDI note. However the static function does the interrupt period calculation on the fly, and is significantly slower although with the benefit of a smaller memory footprint.

The `getPin` function uses some basic math in lieu of a lookup table to save on memory, and cannot be overloaded. If you're using a custom pin arrangement for your drives I would recommend using the `sendMoppy` function in combination with a pin array and some bounds checking.

All three of these functions include bounds-checking. `getPeriod` will return a '0' value for out of range notes, while `getPin` will return '-1' for out of range drives.

### Range Guards

	static boolean 
	  checkChannel(uint8_t channel),
	  checkRange  (uint8_t note),
	  checkInputs (uint8_t channel, uint8_t note),

	  checkMIDIChannel(uint8_t channel),
	  checkMIDIRange  (uint8_t note),
	  checkMIDIInputs (uint8_t channel, uint8_t note);

These range guards are automatically invoked by the `sendNote` functions and the `getPeriod / getPin` functions. The three `checkMIDI` functions are unused, but are available for debugging and utility purposes.

### Interrupt Resolution

	    void setResolution(uint16_t resolution);
	uint16_t getResolution();

The Moppy code on the Arduino uses an interrupt resolution of 40 microseconds by default. If you've changed this for whatever reason, the library allows you to adjust the resolution for the array of microsecond periods. This is processing-intensive, so it's recommended to set the resolution before you begin receiving data.

### Data Sends
	void sendMoppy(uint8_t pin, uint16_t period);

	static void
	  sendMoppy  (Stream &port, uint8_t pin, uint16_t period),
	  void sendNoteOn (Stream &port, uint8_t channel, uint8_t note),
	  void sendNoteOff(Stream &port, uint8_t channel, uint8_t note);

In addition to the basic `sendNoteOn` and `sendNoteOff` functions, the library includes a `sendMoppy` function that sends custom pin and period data to the Moppy controller. This function includes no range guards, so use it with caution!

I've also made all three `send` functions available statically, so you can use the library without building a MIDItoMoppy object if you're running low on SRAM. Although this is not recommened due to the performance hit.

### Reset

	void
	  resetResolution(),
	  reset();
        
`resetResolution` will revert the musical period array back to the default Moppy resolution of 40 microseconds if it has been changed. Currently, `reset` does the same. The latter may change in upcoming versions.

If you have enough RAM, I would recommend creating a second object.

## Credits

A big thanks to [SammyIAm](https://github.com/SammyIAm/), who developed [the original Moppy code](https://github.com/SammyIAm/Moppy) and who inspired me to build my own set of musical floppy drives. Thanks Sam!

## License
**Released under the [MIT license](https://opensource.org/licenses/MIT).**

*Developed by David Madison - 2017*
