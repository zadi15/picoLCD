#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "pico/binary_info.h"
#include "LCDops.h"

/*
Copyright (c) 2021, zadi15 (https://github.com/zadi15/)
License can be found at picoLCD/LICENSE
*/

void LCDactivatePreChar(int characterNum, int preset){
    switch (preset){
        case 1: //Music note
            LCDcreateCharacter(characterNum, "00000001", "00000011", "00000111", "00001101", "00001001", "00001011", "00011011", "00011000");
            break;
        case 2: //tick
            LCDcreateCharacter(characterNum, "00000000", "00000000", "00000001", "00000011", "00010110", "00011100", "00001000", "00000000");
            break;
        case 3: //alarm bell
            LCDcreateCharacter(characterNum, "00000100", "00001110", "00001110", "00001110", "00001110", "00011111", "00000100", "00000000");
            break;
        case 4: //up arrow
            LCDcreateCharacter(characterNum, "00000100", "00001110", "00010101", "00000100", "00000100", "00000100", "00000100", "00000000");
            break;
        case 5: //down arroe
            LCDcreateCharacter(characterNum, "00000100", "00000100", "00000100", "00000100", "00010101", "00001110", "00000100", "00000000");
            break;
        case 6: //Lock Locked
            LCDcreateCharacter(characterNum, "00000000", "00001110", "00010001", "00010001", "00011111", "00011011", "00011111", "00000000");
            break;
        case 7: //Lock Unlocked
            LCDcreateCharacter(characterNum, "00000000", "00001110", "00010001", "00000001", "00011111", "00011011", "00011111", "00000000");
            break;
        case 8: //Play
            LCDcreateCharacter(characterNum, "00000000", "00001000", "00001100", "00001110", "00001110", "00001100", "00001000", "0000000");
            break;
        case 9: //Pause
            LCDcreateCharacter(characterNum, "00000000", "00011011", "00011011", "00011011", "00011011", "00011011", "00011011", "00000000");
            break;
        case 10: //Next Track
            LCDcreateCharacter(characterNum, "00000000", "00001001", "00001101", "00001111", "00001111", "00001101", "00001001", "0000000");
            break;
        case 11: //Previous Track
            LCDcreateCharacter(characterNum, "00000000", "00010010", "00010110", "00011110", "00011110", "00010110", "00010010", "00000000");
            break;
        case 12: //Repeat Track
            LCDcreateCharacter(characterNum, "00000010", "00011111", "00010010", "00000000", "00001001", "00011111", "00001000", "00000000");
            break;
        case 13: //Shuffle Track
            LCDcreateCharacter(characterNum, "00001110", "00010000", "00001110", "00000001", "00001110", "00000000", "00001010", "00010101");
            break;
        case 14: //Muted
            LCDcreateCharacter(characterNum, "00010001", "00011011", "00010101", "00010001", "00010001", "00000000", "00010101", "00001010");
            break;
        case 15: //Smiley Face
            LCDcreateCharacter(characterNum, "00000000", "00000000", "00001010", "00000000", "00010001", "00001110", "00000000", "00000000");
            break;
        case 16: //Frowny Face
            LCDcreateCharacter(characterNum, "00000000", "00000000", "00001010", "00000000", "00001110", "00010001", "00000000", "00000000");
            break;
        case 17: //Person
            LCDcreateCharacter(characterNum, "00000000", "00001110", "00001110", "00000100", "00011111", "00001110", "00001110", "00000000");
            break;
        case 18: //Heart
            LCDcreateCharacter(characterNum, "00000000", "00001010", "00011111", "00011111", "00001110", "00000100", "00000000", "00000000");
            break;
        case 19: //Battery_empty
            LCDcreateCharacter(characterNum, "00000100", "00011111", "00010001", "00010001", "00010001", "00010001", "00011111", "00000000");
            break;
        case 20: //Battery_1
            LCDcreateCharacter(characterNum, "00000100", "00011111", "00010001", "00010001", "00010001", "00011111", "00011111", "00000000");
            break;
        case 21: //Battery_2
            LCDcreateCharacter(characterNum, "00000100", "00011111", "00010001", "00010001", "00011111", "00011111", "00011111", "00000000");
            break;
        case 22: //Battery_3
            LCDcreateCharacter(characterNum, "00000100", "00011111", "00010001", "00011111", "00011111", "00011111", "00011111", "00000000");
            break;
        case 23: //Battery_full
            LCDcreateCharacter(characterNum, "00000100", "00011111", "00011111", "00011111", "00011111", "00011111", "00011111", "00000000");
            break;
        case 24: //Battery_charging
            LCDcreateCharacter(characterNum, "00000100", "00011111", "00010001", "00010101", "00010101", "00010001", "00011111", "00000000");
            break;
        case 25: //Ohm
            LCDcreateCharacter(characterNum, "00000000", "00001110", "00010001", "00010001", "00010001", "00001010", "00011011", "00000000");
            break;
        case 26: //Square Root
            LCDcreateCharacter(characterNum, "00000000", "00000000", "00000011", "00000100", "00000100", "00010100", "00001000", "00000000");
            break;
        case 27: //Pi
            LCDcreateCharacter(characterNum, "00000000", "00011111", "00001010", "00001010", "00001010", "00010011", "00000000", "00000000");
            break;
        case 28: //:D
            LCDcreateCharacter(characterNum, "00000000", "00001010", "00000000", "00011111", "00010001", "00001110", "00000000", "00000000");
            break;
        case 29: //>:(
            LCDcreateCharacter(characterNum, "00010001", "00001010", "00010001", "00000100", "00000000", "00001110", "00010001", "00000000");
            break;
        case 30: //:O
            LCDcreateCharacter(characterNum, "00000000", "00001010", "00000000", "00001110", "00010001", "00010001", "00001110", "00000000");
            break;
    }
}
/*
: //
    LCDcreateCharacter(characterNum, "", "", "", "", "", "", "", "");
    break;
case
*/
