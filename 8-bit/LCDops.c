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

void LCDinit(){
    sleep_ms(8);
    //Increment mode for the cursor 0x06 - 0000 0110
    gpio_put(LCDpins[0], false);
    gpio_put(LCDpins[1], true);
    gpio_put(LCDpins[2], true);
    gpio_put(LCDpins[3], false);
    gpio_put(LCDpins[4], false);
    gpio_put(LCDpins[5], false);
    gpio_put(LCDpins[6], false);
    gpio_put(LCDpins[7], false);
    E_INSTRUCTION();

    sleep_ms(8);
    //Display on, cursor on, blink on 0x0C - 0000 1111
    gpio_put(LCDpins[0], true);
    gpio_put(LCDpins[1], true);
    gpio_put(LCDpins[2], true);
    gpio_put(LCDpins[3], true);
    gpio_put(LCDpins[4], false);
    gpio_put(LCDpins[5], false);
    gpio_put(LCDpins[6], false);
    gpio_put(LCDpins[7], false);
    sleep_ms(5);
    E_INSTRUCTION();

    sleep_ms(8);
    //8-bit data bus, 2 line display 0x38 - 00111000
    gpio_put(LCDpins[0], false);
    gpio_put(LCDpins[1], false);
    gpio_put(LCDpins[2], false);
    if (LCDpins[12] == 1){
        gpio_put(LCDpins[3], false);
    } else {
        gpio_put(LCDpins[3], true);
    }
    gpio_put(LCDpins[4], true);
    gpio_put(LCDpins[5], true);
    gpio_put(LCDpins[6], false);
    gpio_put(LCDpins[7], false);
    E_INSTRUCTION();
}
void LCDclear(){
    sleep_ms(8);
    //Clear Dispaly 0x01 - 00000001
    gpio_put(LCDpins[0], true);
    gpio_put(LCDpins[1], false);
    gpio_put(LCDpins[2], false);
    gpio_put(LCDpins[3], false);
    gpio_put(LCDpins[4], false);
    gpio_put(LCDpins[5], false);
    gpio_put(LCDpins[6], false);
    gpio_put(LCDpins[7], false);
    E_INSTRUCTION();

    sleep_ms(8);
    //Return Display if moved 0x02 - 00000010
    gpio_put(LCDpins[0], false);
    gpio_put(LCDpins[1], true);
    gpio_put(LCDpins[2], false);
    gpio_put(LCDpins[3], false);
    gpio_put(LCDpins[4], false);
    gpio_put(LCDpins[5], false);
    gpio_put(LCDpins[6], false);
    gpio_put(LCDpins[7], false);
    E_INSTRUCTION();

    sleep_ms(8);
    //Move cursor to 0,0 0x80 - 10000000
    gpio_put(LCDpins[0], false);
    gpio_put(LCDpins[1], false);
    gpio_put(LCDpins[2], false);
    gpio_put(LCDpins[3], false);
    gpio_put(LCDpins[4], false);
    gpio_put(LCDpins[5], false);
    gpio_put(LCDpins[6], false);
    gpio_put(LCDpins[7], true);
    E_INSTRUCTION();
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
void LCDsendRawInstruction(int RS_PIN, int RW_PIN, char binary[]){
    binIns(binary);
    if (RS_PIN == 0){
        gpio_put(LCDpins[9], false);
    } else{
        gpio_put(LCDpins[9], true);
    }
    if (RS_PIN == 0){
        E_INSTRUCTION();
    } else{
        E_DATA();
    }
    gpio_put(LCDpins[9], false);
}

void LCDwriteAscii(int code){
    decToBin(code);
    E_DATA();
}
