# picoLCD

## About picoLCD
picoLCD is a collection of functions to make interfacing with HD44780 based LCD screens easier
on the Raspberry Pi Pico. Rather than reading through data sheets to figure out the correct set
of instructions to send to the screen, picoLCD attempts to make it a simpler process, while still being
extremely versatile. It's as simple as copying the `.c & .h` files to your project, add some
`#include`s, set some pins and off you go!

This is still very much a work in progress.
This is known to work on the following LCD sizes in 8-bit mode:

![16x2 status](https://img.shields.io/badge/16x2-Tested-brightgreen)

![20x4 status](https://img.shields.io/badge/20x4-Testing-orange)

![40x2 status](https://img.shields.io/badge/40x2-Testing-orange)

![16x4 status](https://img.shields.io/badge/16x4-Untested-red)

4-bit operation is also on the way once more progress is done on the current version.

Basic Instructions are below, with more detailed function documentation in 'picoLCD/FUNCTIONS.md'

Current Version = 0.0.1
### Wiring the pico

The Pico should be wired to the LCD as follows for 8-bit operation, with the Pico being plugged
into USB:

![diagram depicting the wiring of the LCD to the PICO](https://raw.githubusercontent.com/zadi15/picoLCD/main/imgs/picoLCD.png)

Please note the LCD backlight should be powered by an external 5v power source, as the Pico may not be able to power both the LCD and
backlight.

## Basic Usage:

All you need to do is move all `.c & .h` files (found at either `picoLCD/8-bit` for 8-bit operation or `picoLCD/4-bit` for 4-bit operation) except main.c to your project folder, and include the following:

At the top of your main file the following `#include`s:

<pre>
#include "pico/binary_info.h"
#include "LCDops.h"
#include "generalOps.h"
</pre>

Additionally, you need to declare which GPIOs the LCD is connected to and the LCD size (Make sure these are not in `main()`). The example below is for a 16x2 LCD connected as in the above diagram.

{D0,D1,D2,D3,D4,D5,D6,D7, E , RS , RW , LCD Line Length (eg. 16 characters across), Number of Lines on LCD}

`int LCDpins[14] = {0,1,2,3,4,5,6,7,15,16,17,16,2};`

Finally these pins that we just defined (excluding the LCD line length and line count values) need to be initialized, set as output and pulled low. Here is an example:

<pre>
for(int gpio = 0; gpio < 11; gpio++){
    gpio_init(LCDpins[gpio]);
    gpio_set_dir(LCDpins[gpio], true);
    gpio_put(LCDpins[gpio], false);
}
</pre>

And inside your `CMakeLists.txt`, add `main.c` and `generalOps.c` to your `add_executable()` e.g.

<pre>
add_executable(picoLCD
    main.c
    LCDops.c
    generalOps.c
)
</pre>

You're now able to use picoLCD's functions as explained in `picoLCD/FUNCTIONS.md`!

An example of a program using picoLCD can be found in `main.c` that writes "Hello World Mr. LCD Screen!" and then inserts a character directly using it's ascii code (from the binary character code).

![LCD screen displaying Hello World Mr. LCD](https://raw.githubusercontent.com/zadi15/picoLCD/main/imgs/screen_low.gif)

## To Do

--> Clean up FUNCTIONS.md

--> Continue adding LCD functions
