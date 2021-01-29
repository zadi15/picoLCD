#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "pico/binary_info.h"
#include "LCDops.h"
#include "generalOps.h"
#include "presetChars.h"

/*
Copyright (c) 2021, zadi15 (https://github.com/zadi15/)
License can be found at picoLCD/LICENSE
*/

int LCDpins[14] = {0,1,2,3,4,5,6,7,15,16,17,20,4};

int main(){
    bi_decl(bi_program_description("This is a work-in-progress example of interfacing with LCD Displays using HD44780 chips on the Raspberry Pi Pico!"));

    stdio_init_all();

    //Initialize all needed pins as defined in LCDpins, set them as
    // outputs and then pull them low
    for(int gpio = 0; gpio < 11; gpio++){
        gpio_init(LCDpins[gpio]);
        gpio_set_dir(LCDpins[gpio], true);
        gpio_put(LCDpins[gpio], false);
    }

    //Initialize and clear the LCD, prepping it for characters / instructions
    LCDinit();
    LCDclear();
    sleep_ms(8);
    LCDactivatePreChar(1, 1);
    LCDactivatePreChar(2, 2);
    LCDactivatePreChar(3, 3);
    LCDactivatePreChar(4, 4);
    LCDactivatePreChar(5, 5);
    LCDactivatePreChar(6, 6);
    LCDactivatePreChar(7, 7);
    LCDactivatePreChar(8, 8);
    LCDgoto("00");
    LCDwriteMessage("1 2 3 4 5 6 7 8");
    LCDgoto("40");
    LCDwriteCustomCharacter(1);
    LCDwriteAscii(32);
    LCDwriteCustomCharacter(2);
    LCDwriteAscii(32);
    LCDwriteCustomCharacter(3);
    LCDwriteAscii(32);
    LCDwriteCustomCharacter(4);
    LCDwriteAscii(32);
    LCDwriteCustomCharacter(5);
    LCDwriteAscii(32);
    LCDwriteCustomCharacter(6);
    LCDwriteAscii(32);
    LCDwriteCustomCharacter(7);
    LCDwriteAscii(32);
    LCDwriteCustomCharacter(8);
    LCDwriteAscii(32);
    sleep_ms(5000);
    LCDactivatePreChar(1, 9);
    LCDactivatePreChar(2, 10);
    LCDactivatePreChar(3, 11);
    LCDactivatePreChar(4, 12);
    LCDactivatePreChar(5, 13);
    LCDactivatePreChar(6, 14);
    LCDactivatePreChar(7, 15);
    LCDactivatePreChar(8, 16);
    LCDgoto("00");
    LCDwriteMessage("9 10111213141516");
    LCDgoto("40");
    LCDwriteCustomCharacter(1);
    LCDwriteAscii(32);
    LCDwriteCustomCharacter(2);
    LCDwriteAscii(32);
    LCDwriteCustomCharacter(3);
    LCDwriteAscii(32);
    LCDwriteCustomCharacter(4);
    LCDwriteAscii(32);
    LCDwriteCustomCharacter(5);
    LCDwriteAscii(32);
    LCDwriteCustomCharacter(6);
    LCDwriteAscii(32);
    LCDwriteCustomCharacter(7);
    LCDwriteAscii(32);
    LCDwriteCustomCharacter(8);
    LCDwriteAscii(32);
    sleep_ms(5000);
    LCDactivatePreChar(1, 17);
    LCDactivatePreChar(2, 18);
    LCDactivatePreChar(3, 19);
    LCDactivatePreChar(4, 20);
    LCDactivatePreChar(5, 21);
    LCDactivatePreChar(6, 22);
    LCDactivatePreChar(7, 23);
    LCDactivatePreChar(8, 24);
    LCDgoto("00");
    LCDwriteMessage("1718192021222324");
    LCDgoto("40");
    LCDwriteCustomCharacter(1);
    LCDwriteAscii(32);
    LCDwriteCustomCharacter(2);
    LCDwriteAscii(32);
    LCDwriteCustomCharacter(3);
    LCDwriteAscii(32);
    LCDwriteCustomCharacter(4);
    LCDwriteAscii(32);
    LCDwriteCustomCharacter(5);
    LCDwriteAscii(32);
    LCDwriteCustomCharacter(6);
    LCDwriteAscii(32);
    LCDwriteCustomCharacter(7);
    LCDwriteAscii(32);
    LCDwriteCustomCharacter(8);
    LCDwriteAscii(32);
    sleep_ms(5000);
    LCDactivatePreChar(1, 25);
    LCDactivatePreChar(2, 26);
    LCDactivatePreChar(3, 27);
    LCDactivatePreChar(4, 28);
    LCDactivatePreChar(5, 29);
    LCDactivatePreChar(6, 30);
    LCDgoto("00");
    LCDwriteMessage("252627282930      ");
    LCDgoto("40");
    LCDwriteCustomCharacter(1);
    LCDwriteAscii(32);
    LCDwriteCustomCharacter(2);
    LCDwriteAscii(32);
    LCDwriteCustomCharacter(3);
    LCDwriteAscii(32);
    LCDwriteCustomCharacter(4);
    LCDwriteAscii(32);
    LCDwriteCustomCharacter(5);
    LCDwriteAscii(32);
    LCDwriteCustomCharacter(6);
    LCDwriteAscii(32);
    LCDwriteAscii(32);
    LCDwriteAscii(32);
    LCDwriteAscii(32);
    LCDwriteAscii(32);
}
