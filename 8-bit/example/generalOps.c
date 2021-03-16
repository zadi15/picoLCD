#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "LCDops.h"

/*
Copyright (c) 2021, zadi15 (https://github.com/zadi15/)
License can be found at picoLCD/LICENSE
*/

extern int LCDpins[14];

void decToBin(int n){
    int count = 0;
    char binaryTmp[9];
    char binaryFinal[9] = "";
    char extras = '0';
    itoa(n,binaryTmp,2);
    count = strlen(binaryTmp);
    while (count < 8){
        strncat(binaryFinal, &extras, 1);
        count++;
    }
    strcat(binaryFinal, binaryTmp);
    count = 0;
    for (int f = strlen(binaryFinal) - 1; f >= 0; f--){
        if (binaryFinal[f] == '0'){
            gpio_put(LCDpins[count], false);
        } else if (binaryFinal[f] == '1'){
            gpio_put(LCDpins[count], true);
        }
        count ++;
    }
}

void binIns(char binaryFinal[]){
    int count = 0;
    for (int f = strlen(binaryFinal) - 1; f >= 0; f--){
        if (binaryFinal[f] == '0'){
            gpio_put(LCDpins[count], false);
        } else if (binaryFinal[f] == '1'){
            gpio_put(LCDpins[count], true);
        }
        count ++;
    }
    sleep_ms(3);
}
