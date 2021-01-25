# picoLCD

## About picoLCD
picoLCD is a collection of functions to make interfacing with HD44780 based LCD screens easier
on the Raspberry Pi Pico. Rather than reading through data sheets to figure out the correct set
of instructions to send to the screen, picoLCD attempts to make it simpler, while still being
extremely versatile. It's as simple as copying the '.c' and '.h' files to your project, add some
'#include's, set some pins and off you go!

This is still very much a work in progress as I only received my Pico recently, and is primarily
designed around 8-bit operation of a 16x2 screen. Other sizes such as 40x2 and 4-bit operation are
also on the way once more progress is done on the current version.

Basic Instructions are below, with more detailed function documentation in 'picoLCD/FUNCTIONS.md'

### Wiring the pico

The Pico should be wired to the LCD as follows for 8-bit operation, with the Pico being plugged
into USB:

![alt text](https://raw.githubusercontent.com/zadi15/picoLCD/main/imgs/picoLCD.png)

## Basic Usage:

An example of how to start with using the functions is shown in 'main.c'.

We will use 'main.c' as the example during the walk-through

The first step is to define these three pins, before your 'main()'.

'const uint E_PIN = 15; // ENABLE PIN -- Toggle hi/lo to send data
const uint RS_PIN = 16; //INSTRUCTION/DATA -- LOW is for sending Instructions, HIGH is for sending Data
const uint RW_PIN = 17; //READWRITE -- LOW is write, High is Read'

You will additionally need to make these available to the other functions, by putting this inside your
'main.h':
'extern uint E_PIN;
extern uint RS_PIN;
extern uint RW_PIN;'

Next, a for loop initializes all of our data pins, sets them as outputs and pulls them low.
'for(int gpio = 0; gpio < 0 + 8; gpio++){
    gpio_init(gpio);
    gpio_set_dir(gpio, true);
    gpio_put(gpio, false);
}'

We then do the same for the 'E_PIN', 'RS_PIN' and 'RW_PIN', and move on to the main functions.
