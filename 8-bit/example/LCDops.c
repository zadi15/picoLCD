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

int LCDdisplay = 0;

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

void detectLCD(){
    switch (LCDpins[11]){
        case 16:
            if (LCDpins[12] == 2){
                LCDdisplay = 1;
            } else if (LCDpins[12] == 4){
                LCDdisplay = 2;
            }
            break;
        case 20:
            if (LCDpins[12] == 2){
                LCDdisplay = 3;
            } else if (LCDpins[12] == 4){
                LCDdisplay = 4;
            }
            break;
        case 40:
            LCDdisplay = 5;
            break;
        default:
            LCDdisplay = 88;
            break;
    }
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
    detectLCD();
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

/*
0 - Not run
1 - 1602
2 - 1604
3 - 2002
4 - 2004
5 - 4002
*/

void LCDwriteMessage(char message[]){
    switch (LCDdisplay){
        case 1:
            for (int i = 0; i < strlen(message); i++){
                if (i == 16) {
                    LCDgoto("40");
                    sleep_ms(3);
                }
                int tmp = (int)message[i];
                decToBin(tmp);
                E_DATA();
            }
            break;
        case 2:
            for (int i = 0; i < strlen(message); i++){
                switch (i){
                    case 16:
                        LCDgoto("40");
                        sleep_ms(3);
                        break;
                    case 32:
                        LCDgoto("14");
                        sleep_ms(3);
                        break;
                    case 48:
                        LCDgoto("54");
                        sleep_ms(3);
                        break;
                }
                int tmp = (int)message[i];
                decToBin(tmp);
                E_DATA();
            }
            break;
        case 3:
            for (int i = 0; i < strlen(message); i++){
                if (i == 20) {
                    LCDgoto("40");
                    sleep_ms(3);
                }
                int tmp = (int)message[i];
                decToBin(tmp);
                E_DATA();
            }
            break;
        case 4:
            for (int i = 0; i < strlen(message); i++){
                switch (i){
                    case 20:
                        LCDgoto("40");
                        //sleep_ms(3);
                        break;
                    case 40:
                        LCDgoto("14");
                        //sleep_ms(3);
                        break;
                    case 60:
                        LCDgoto("54");
                        //sleep_ms(3);
                        break;
                }
                int tmp = (int)message[i];
                decToBin(tmp);
                E_DATA();
            }
            break;
        case 5:
            for (int i = 0; i < strlen(message); i++){
                int tmp = (int)message[i];
                decToBin(tmp);
                E_DATA();
            }
            break;
        default:
            for (int i = 0; i < strlen(message); i++){
                if (i == 16) {
                    LCDgoto("40");
                    sleep_ms(3);
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
