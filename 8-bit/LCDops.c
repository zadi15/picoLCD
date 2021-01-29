#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "pico/binary_info.h"
#include "generalOps.h"

/*
Copyright (c) 2021, zadi15 (https://github.com/zadi15/)
License can be found at picoLCD/LICENSE
*/

extern int LCDpins[14];

void E_INSTRUCTION(){
    gpio_put(LCDpins[9], false);
    sleep_ms(5);
    gpio_put(LCDpins[8], true);
    sleep_ms(5);
    gpio_put(LCDpins[8], false);
}
void E_DATA(){
    gpio_put(LCDpins[9], true);
    sleep_ms(5);
    gpio_put(LCDpins[8], true);
    sleep_ms(5);
    gpio_put(LCDpins[8], false);
    sleep_ms(5);
    gpio_put(LCDpins[9], false);
}

void LCDsendRawInstruction(int RS_PIN, int RW_PIN, char binary[]){
    binIns(binary);
    if (RW_PIN == 0){
        gpio_put(LCDpins[10], false);
    } else{
        gpio_put(LCDpins[10], true);
    }
    if (RS_PIN == 0){
        E_INSTRUCTION();
    } else{
        E_DATA();
    }
    gpio_put(LCDpins[9], false);
}

void LCDinit(){
    sleep_ms(8);
    //Increment mode for the cursor 0x06 - 0000 0110
    LCDsendRawInstruction(0,0,"00000110");
    sleep_ms(8);
    //Display on, cursor on, blink on 0x0C - 0000 1111
    LCDsendRawInstruction(0,0,"00001111");
    sleep_ms(8);
    //8-bit data bus, 2 line display 0x38 - 00111000
    if (LCDpins[12] == 1){
        LCDsendRawInstruction(0,0,"00110000");
    } else {
        LCDsendRawInstruction(0,0,"00111000");
    }
}
void LCDclear(){
    sleep_ms(8);
    //Clear Dispaly 0x01 - 00000001
    LCDsendRawInstruction(0,0,"00000001");
    sleep_ms(8);
    //Return Display if moved 0x02 - 00000010
    LCDsendRawInstruction(0,0,"00000010");
    sleep_ms(8);
    //Move cursor to 0,0 0x80 - 10000000
LCDsendRawInstruction(0,0,"10000000");
}

void LCDgoto(char hexstring[]){
    int hexDec = (int)strtol(hexstring, NULL, 16);
    decToBin(hexDec);
    gpio_put(LCDpins[7], true);
    E_INSTRUCTION();
    sleep_ms(8);
}

void LCDwriteMessage(char message[]){
    switch (LCDpins[11]){
        case 16:
            if (LCDpins[12] == 2){
                for (int i = 0; i < strlen(message); i++){
                    if (i == 16) {
                        LCDgoto("40");
                        sleep_ms(5);
                    }
                    int tmp = (int)message[i];
                    decToBin(tmp);
                    E_DATA();
                }
            } else if (LCDpins[13] == 4){
                for (int i = 0; i < strlen(message); i++){
                    switch (i){
                        case 16:
                            LCDgoto("40");
                            sleep_ms(5);
                            break;
                        case 32:
                            LCDgoto("14");
                            sleep_ms(5);
                            break;
                        case 48:
                            LCDgoto("54");
                            sleep_ms(5);
                            break;
                    }
                    int tmp = (int)message[i];
                    decToBin(tmp);
                    E_DATA();
                }
            }
            break;
        case 20:
            if (LCDpins[12] == 2){
                for (int i = 0; i < strlen(message); i++){
                    if (i == 20) {
                        LCDgoto("40");
                        sleep_ms(5);
                    }
                    int tmp = (int)message[i];
                    decToBin(tmp);
                    E_DATA();
                }
            } else if (LCDpins[13] == 4){
                for (int i = 0; i < strlen(message); i++){
                    switch (i){
                        case 20:
                            LCDgoto("40");
                            sleep_ms(5);
                            break;
                        case 40:
                            LCDgoto("14");
                            sleep_ms(5);
                            break;
                        case 60:
                            LCDgoto("54");
                            sleep_ms(5);
                            break;
                    }
                    int tmp = (int)message[i];
                    decToBin(tmp);
                    E_DATA();
                }
            }
            break;
        default:
        for (int i = 0; i < strlen(message); i++){
            if (i == 16) {
                LCDgoto("40");
                sleep_ms(5);
            }
            int tmp = (int)message[i];
            decToBin(tmp);
            E_DATA();
        }
            break;
    }
}

void LCDwriteRawMessage(char message[]){
    for (int i = 0; i < strlen(message); i++){
        int tmp = (int)message[i];
        decToBin(tmp);
        E_DATA();
    }
}

void LCDwriteAscii(int code){
    decToBin(code);
    E_DATA();
}

void LCDdisplayControl(int display, int cursor, int blink){
    char binary[] = "";
    sprintf(binary, "00001%d%d%d", display, cursor, blink);
    LCDsendRawInstruction(0, 0, binary);
}

void LCDcreateCharacter(int charnum, char line1[], char line2[], char line3[], char line4[], char line5[], char line6[], char line7[], char line8[]){
    switch (charnum) {
        case 1:
            LCDsendRawInstruction(0,0,"01000000");
            LCDsendRawInstruction(1,0,line1);
            LCDsendRawInstruction(1,0,line2);
            LCDsendRawInstruction(1,0,line3);
            LCDsendRawInstruction(1,0,line4);
            LCDsendRawInstruction(1,0,line5);
            LCDsendRawInstruction(1,0,line6);
            LCDsendRawInstruction(1,0,line7);
            LCDsendRawInstruction(1,0,line8);
            sleep_ms(8);
            break;
        case 2:
            LCDsendRawInstruction(0,0,"01001000");
            LCDsendRawInstruction(1,0,line1);
            LCDsendRawInstruction(1,0,line2);
            LCDsendRawInstruction(1,0,line3);
            LCDsendRawInstruction(1,0,line4);
            LCDsendRawInstruction(1,0,line5);
            LCDsendRawInstruction(1,0,line6);
            LCDsendRawInstruction(1,0,line7);
            LCDsendRawInstruction(1,0,line8);
            sleep_ms(8);
            break;
        case 3:
            LCDsendRawInstruction(0,0,"01010000");
            LCDsendRawInstruction(1,0,line1);
            LCDsendRawInstruction(1,0,line2);
            LCDsendRawInstruction(1,0,line3);
            LCDsendRawInstruction(1,0,line4);
            LCDsendRawInstruction(1,0,line5);
            LCDsendRawInstruction(1,0,line6);
            LCDsendRawInstruction(1,0,line7);
            LCDsendRawInstruction(1,0,line8);
            sleep_ms(8);
            break;
        case 4:
            LCDsendRawInstruction(0,0,"01011000");
            LCDsendRawInstruction(1,0,line1);
            LCDsendRawInstruction(1,0,line2);
            LCDsendRawInstruction(1,0,line3);
            LCDsendRawInstruction(1,0,line4);
            LCDsendRawInstruction(1,0,line5);
            LCDsendRawInstruction(1,0,line6);
            LCDsendRawInstruction(1,0,line7);
            LCDsendRawInstruction(1,0,line8);
            sleep_ms(8);
            break;
        case 5:
            LCDsendRawInstruction(0,0,"01100000");
            LCDsendRawInstruction(1,0,line1);
            LCDsendRawInstruction(1,0,line2);
            LCDsendRawInstruction(1,0,line3);
            LCDsendRawInstruction(1,0,line4);
            LCDsendRawInstruction(1,0,line5);
            LCDsendRawInstruction(1,0,line6);
            LCDsendRawInstruction(1,0,line7);
            LCDsendRawInstruction(1,0,line8);
            sleep_ms(8);
            break;
        case 6:
            LCDsendRawInstruction(0,0,"01101000");
            LCDsendRawInstruction(1,0,line1);
            LCDsendRawInstruction(1,0,line2);
            LCDsendRawInstruction(1,0,line3);
            LCDsendRawInstruction(1,0,line4);
            LCDsendRawInstruction(1,0,line5);
            LCDsendRawInstruction(1,0,line6);
            LCDsendRawInstruction(1,0,line7);
            LCDsendRawInstruction(1,0,line8);
            sleep_ms(8);
            break;
        case 7:
            LCDsendRawInstruction(0,0,"01110000");
            LCDsendRawInstruction(1,0,line1);
            LCDsendRawInstruction(1,0,line2);
            LCDsendRawInstruction(1,0,line3);
            LCDsendRawInstruction(1,0,line4);
            LCDsendRawInstruction(1,0,line5);
            LCDsendRawInstruction(1,0,line6);
            LCDsendRawInstruction(1,0,line7);
            LCDsendRawInstruction(1,0,line8);
            sleep_ms(8);
            break;
        case 8:
            LCDsendRawInstruction(0,0,"01111000");
            LCDsendRawInstruction(1,0,line1);
            LCDsendRawInstruction(1,0,line2);
            LCDsendRawInstruction(1,0,line3);
            LCDsendRawInstruction(1,0,line4);
            LCDsendRawInstruction(1,0,line5);
            LCDsendRawInstruction(1,0,line6);
            LCDsendRawInstruction(1,0,line7);
            LCDsendRawInstruction(1,0,line8);
            sleep_ms(8);
            break;
    }
}

void LCDwriteCustomCharacter(int characterNum){
    sleep_ms(8);
    switch (characterNum){
        case 1:
            LCDsendRawInstruction(1,0,"00000000");
            break;
        case 2:
            LCDsendRawInstruction(1,0,"00000001");
            break;
        case 3:
            LCDsendRawInstruction(1,0,"00000010");
            break;
        case 4:
            LCDsendRawInstruction(1,0,"00000011");
            break;
        case 5:
            LCDsendRawInstruction(1,0,"00000100");
            break;
        case 6:
            LCDsendRawInstruction(1,0,"00000101");
            break;
        case 7:
            LCDsendRawInstruction(1,0,"00000110");
            break;
        case 8:
            LCDsendRawInstruction(1,0,"00000111");
            break;
    }
}

void LCDshiftCursor(int rl){
    if (rl == 0){
        LCDsendRawInstruction(0,0,"00010000");
    } else {
        LCDsendRawInstruction(0,0,"00010100");
    }
}

void LCDshiftDisplay(int rl){
    if (rl == 0){
        LCDsendRawInstruction(0,0,"00011000");
    } else {
        LCDsendRawInstruction(0,0,"00011100");
    }
}

void LCDactivatePreChar(int characterNum, int preset){
    switch (preset){
        /*
        1:
            LCDcreateCharacter(characterNum, "", "", "", "", "", "", "", "");
            break;
        case         */
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
            LCDcreateCharacter(characterNum, "00000000", "00001001", "00001101", "00001111", "00001111", "00001101", "00001001", "0000001");
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
    }
}
