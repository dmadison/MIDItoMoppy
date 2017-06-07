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
 
#ifndef MusicalPeriods_h
#define MusicalPeriods_h

#include <avr/pgmspace.h>

/*
 * Defines floppy drive note periods and stores them into program memory
 *
 * Notes are stored as the period, in microseconds, between wave peaks. Microsecond periods were calculated with this formula: 1000000 / <frequency>.
 * Musical note frequency table from MIT: http://www.phy.mtu.edu/~suits/notefreqs.html
 *
 * Notes range: C1 - B4, or 24-71 where 60 = C4. Note names follow scientific note notation.
*/

// C1 - B1
#define MICRO_PERIOD_C1  30581
#define MICRO_PERIOD_Db1 28860
#define MICRO_PERIOD_D1  27241
#define MICRO_PERIOD_Eb1 25714
#define MICRO_PERIOD_E1  24272
#define MICRO_PERIOD_F1  22910
#define MICRO_PERIOD_Gb1 21622
#define MICRO_PERIOD_G1  20408
#define MICRO_PERIOD_Ab1 19264
#define MICRO_PERIOD_A1  18182
#define MICRO_PERIOD_Bb1 17161
#define MICRO_PERIOD_B1  16197

// C2 - B2
#define MICRO_PERIOD_C2  15288
#define MICRO_PERIOD_Db2 14430
#define MICRO_PERIOD_D2  13620
#define MICRO_PERIOD_Eb2 12857
#define MICRO_PERIOD_E2  12134
#define MICRO_PERIOD_F2  11453
#define MICRO_PERIOD_Gb2 10811
#define MICRO_PERIOD_G2  10204
#define MICRO_PERIOD_Ab2 9631
#define MICRO_PERIOD_A2  9091
#define MICRO_PERIOD_Bb2 8581
#define MICRO_PERIOD_B2  8099

// C3 - B3
#define MICRO_PERIOD_C3  7645
#define MICRO_PERIOD_Db3 7216
#define MICRO_PERIOD_D3  6811
#define MICRO_PERIOD_Eb3 6428
#define MICRO_PERIOD_E3  6068
#define MICRO_PERIOD_F3  5727
#define MICRO_PERIOD_Gb3 5405
#define MICRO_PERIOD_G3  5102
#define MICRO_PERIOD_Ab3 4816
#define MICRO_PERIOD_A3  4545
#define MICRO_PERIOD_Bb3 4290
#define MICRO_PERIOD_B3  4050

// C4 - B4
#define MICRO_PERIOD_C4  3822
#define MICRO_PERIOD_Db4 3608
#define MICRO_PERIOD_D4  3405
#define MICRO_PERIOD_Eb4 3214
#define MICRO_PERIOD_E4  3034
#define MICRO_PERIOD_F4  2863
#define MICRO_PERIOD_Gb4 2703
#define MICRO_PERIOD_G4  2551
#define MICRO_PERIOD_Ab4 2408
#define MICRO_PERIOD_A4  2273
#define MICRO_PERIOD_Bb4 2145
#define MICRO_PERIOD_B4  2025

const uint16_t MicroPeriods[48] PROGMEM = {
	// C1 - B1
	MICRO_PERIOD_C1,
	MICRO_PERIOD_Db1,
	MICRO_PERIOD_D1,
	MICRO_PERIOD_Eb1,
	MICRO_PERIOD_E1,
	MICRO_PERIOD_F1,
	MICRO_PERIOD_Gb1,
	MICRO_PERIOD_G1,
	MICRO_PERIOD_Ab1,
	MICRO_PERIOD_A1,
	MICRO_PERIOD_Bb1,
	MICRO_PERIOD_B1,

	// C2 - B2
	MICRO_PERIOD_C2,
	MICRO_PERIOD_Db2,
	MICRO_PERIOD_D2,
	MICRO_PERIOD_Eb2,
	MICRO_PERIOD_E2,
	MICRO_PERIOD_F2,
	MICRO_PERIOD_Gb2,
	MICRO_PERIOD_G2,
	MICRO_PERIOD_Ab2,
	MICRO_PERIOD_A2,
	MICRO_PERIOD_Bb2,
	MICRO_PERIOD_B2,

	// C3 - B3
	MICRO_PERIOD_C3,
	MICRO_PERIOD_Db3,
	MICRO_PERIOD_D3,
	MICRO_PERIOD_Eb3,
	MICRO_PERIOD_E3,
	MICRO_PERIOD_F3,
	MICRO_PERIOD_Gb3,
	MICRO_PERIOD_G3,
	MICRO_PERIOD_Ab3,
	MICRO_PERIOD_A3,
	MICRO_PERIOD_Bb3,
	MICRO_PERIOD_B3,

	// C4 - B4
	MICRO_PERIOD_C4,
	MICRO_PERIOD_Db4,
	MICRO_PERIOD_D4,
	MICRO_PERIOD_Eb4,
	MICRO_PERIOD_E4,
	MICRO_PERIOD_F4,
	MICRO_PERIOD_Gb4,
	MICRO_PERIOD_G4,
	MICRO_PERIOD_Ab4,
	MICRO_PERIOD_A4,
	MICRO_PERIOD_Bb4,
	MICRO_PERIOD_B4
};

#endif

