# picoLCD

## About picoLCD
picoLCD is a collection of functions to make interfacing with HD44780 based LCD screens easier
on the Raspberry Pi Pico. Rather than reading through data sheets to figure out the correct set
of instructions to send to the screen, picoLCD attempts to make it a simpler process, while still being
extremely versatile. It's as simple as copying the `.c & .h` files to your project, add some
`#include`s, set some pins and off you go!

This is still very much a work in progress as I only received my Pico recently, and is primarily
designed around 8-bit operation of a 16x2 screen. 4-bit operation is also on the way once more progress is done on the current version.

Basic Instructions are below, with more detailed function documentation in 'picoLCD/FUNCTIONS.md'

### Wiring the pico

The Pico should be wired to the LCD as follows for 8-bit operation, with the Pico being plugged
into USB:

![alt text](https://raw.githubusercontent.com/zadi15/picoLCD/main/imgs/picoLCD.png)

## Basic Usage:

All you need to do is move all `.c & .h` files (found at either `picoLCD/8-bit` for 8-bit operation or `picoLCD/4-bit` for 4-bit operation) except main.c to your project folder, and include the following:

At the top of your main file the following `#include`s:

`#include "pico/binary_info.h"
#include "LCDops.h"
#include "generalOps.h"`

Additionally, you need to declare which GPIOs the LCD is connected to and the LCD size (Make sure these are not in `main()`). The example below is for a 16x2 LCD connected as in the above diagram.

{D0,D1,D2,D3,D4,D5,D6,D7,E ,RS ,RW ,LCD Line Length (eg. 16 characters across), Number of Lines on LCD}

`int LCDpins[14] = {0,1,2,3,4,5,6,7,15,16,17,16,2};`

Finally these pins that we just defined (excluding the LCD line length and line count values) need to be initialized, set as output and pulled low. Here is an example:

`for(int gpio = 0; gpio < 11; gpio++){
    gpio_init(LCDpins[gpio]);
    gpio_set_dir(LCDpins[gpio], true);
    gpio_put(LCDpins[gpio], false);
}`

You're now able to use picoLCD's functions as explained in `picoLCD/FUNCTIONS.md`!

An example of a program using picoLCD can be  
