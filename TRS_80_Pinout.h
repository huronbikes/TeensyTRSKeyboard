#ifndef TRS_80_PINOUT_
#define TRS_80_PINOUT_

/*
 * Defines the pinout from the TRS-80 Model 100 keyboard to the microcontroller.
 * 
 * In this case, the device is a Teensy 4.0.
 * 
 * We are using row and column terms not in reference to the phsical layout of the
 * keyboard but rather in reference to the key map layout in the TRS-80 Model 100
 * service manual.
 * 
 * The theory of operation is that the microcontroller will get set up
 * with all the column pins (wires 1 through 9 on on the keyboard, which
 * should all be black in color) as OUTPUT driven HIGH initially.
 * 
 * The row pins (wires 12-19 on the keyboard, all white in color) are then
 * set up as INPUT (INPUT_PULLUP in this case on the Teensy).
 * Pin 20 on the keyboard connector (the furthestmost white wire) is a ground, and
 * Pins 10 and 11 are not connected.
 * 
 * On the TRS-80 Model 100, the keyboard is connected to a 2KB RAM module, with the
 * white connector first going to an octal buffer.  Normally each of the active black wires are
 * tied to VDD (typically 5 volts) with 100k ohm resistors and each of the active white
 * wires are tied to VDD via 33k ohm restistors and ground with a 82 pf capicator (I think this
 * is done as a lowpass filter).
 * 
 * On the Teensy, we want all inputs to get pulled high and start with all outputs driven high.
 * In order to detect a keypress, for each column line on the black wires, the line is driven low.
 * The first row to have an input that then reads as low is then used to map to the key.  Note that
 * this only affects the non-modifier keys.
 * The 7 modifier keys (CTRL, CAPS LOCK, GRPH, CODE, NUM, SHIFT, and PAUSE/BREAK on the keyboard) are read
 * separately since those keys are separated from the rest by diodes and can be pressed in combination.
 */

#define CN_BLACK_1 14
#define CN_BLACK_2 15
#define CN_BLACK_3 16
#define CN_BLACK_4 18
#define CN_BLACK_5 17
#define CN_BLACK_6 19
#define CN_BLACK_7 20
#define CN_BLACK_8 21
#define CN_BLACK_9 22
#define CN_WHITE_11 4
#define CN_WHITE_12 5
#define CN_WHITE_13 6
#define CN_WHITE_14 7
#define CN_WHITE_15 8
#define CN_WHITE_16 9
#define CN_WHITE_17 10
#define CN_WHITE_18 11

#define MODIFIER_COL CN_BLACK_9
#endif
