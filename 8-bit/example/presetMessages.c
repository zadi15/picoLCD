#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "pico/binary_info.h"
#include "LCDops.h"
#include "generalOps.h"

/*
Copyright (c) 2021, zadi15 (https://github.com/zadi15/)
License can be found at picoLCD/LICENSE
*/

extern int LCDpins[14];

extern int LCDdisplay;
/*
0 - Not run
1 - 1602
2 - 1604
3 - 2002
4 - 2004
5 - 4002
*/

int lastRan = 0;

void LCDactivateImpMess(){
    if (LCDdisplay == 0){
        detectLCD();
    }
    LCDclear();
    switch (LCDdisplay){
        case 1:
            LCDdisplayControl(0, 0, 0);
            LCDwriteMessage("+---IMPORTANT--++---MESSAGE!---+");
            sleep_ms(500);
            LCDdisplayControl(1, 0, 0);
            sleep_ms(500);
            LCDdisplayControl(0, 0, 0);
            sleep_ms(500);
            LCDdisplayControl(1, 0, 0);
            sleep_ms(500);
            LCDdisplayControl(0, 0, 0);
            LCDclear();
            LCDwriteRawMessage("+---MESSAGE:---+");
            sleep_ms(100);
            LCDdisplayControl(1, 0, 0);
            break;
        case 2:
            LCDdisplayControl(0, 0, 0);
            LCDwriteMessage("+--------------+|   IMPORTANT  ||    MESSAGE   |+--------------+");
            sleep_ms(500);
            LCDdisplayControl(1, 0, 0);
            sleep_ms(500);
            LCDdisplayControl(0, 0, 0);
            sleep_ms(500);
            LCDdisplayControl(1, 0, 0);
            sleep_ms(500);
            LCDdisplayControl(0, 0, 0);
            LCDclear();
            LCDwriteRawMessage("+---IMPORTANT--+");
            LCDgoto("54");
            LCDwriteRawMessage("+----MESSAGE---+");
            sleep_ms(100);
            LCDdisplayControl(1, 0, 0);
            break;
        case 3:
            LCDdisplayControl(0, 0, 0);
            LCDwriteMessage("+-----IMPORTANT----++-----MESSAGE!-----+");
            sleep_ms(500);
            LCDdisplayControl(1, 0, 0);
            sleep_ms(500);
            LCDdisplayControl(0, 0, 0);
            sleep_ms(500);
            LCDdisplayControl(1, 0, 0);
            sleep_ms(500);
            LCDdisplayControl(0, 0, 0);
            LCDclear();
            LCDwriteRawMessage("+-----MESSAGE:-----+");
            sleep_ms(100);
            LCDdisplayControl(1, 0, 0);
            break;
        case 4:
            LCDdisplayControl(0, 0, 0);
            LCDwriteMessage("+------------------+|     IMPORTANT    ||      MESSAGE     |+------------------+");
            sleep_ms(500);
            LCDdisplayControl(1, 0, 0);
            sleep_ms(500);
            LCDdisplayControl(0, 0, 0);
            sleep_ms(500);
            LCDdisplayControl(1, 0, 0);
            sleep_ms(500);
            LCDdisplayControl(0, 0, 0);
            LCDclear();
            LCDwriteRawMessage("+-----IMPORTANT----+");
            LCDgoto("54");
            LCDwriteRawMessage("+------MESSAGE-----+");
            sleep_ms(100);
            LCDdisplayControl(1, 0, 0);
            break;
        case 5:
            LCDdisplayControl(0, 0, 0);
            LCDwriteMessage("|------IMPORTANT-MESSAGE-RECEIVED------||--------------------------------------|");
            sleep_ms(500);
            LCDdisplayControl(1, 0, 0);
            sleep_ms(500);
            LCDdisplayControl(0, 0, 0);
            sleep_ms(500);
            LCDdisplayControl(1, 0, 0);
            sleep_ms(500);
            LCDdisplayControl(0, 0, 0);
            LCDclear();
            LCDwriteMessage("+------IMPORTANT-MESSAGE-RECEIVED------+");
            LCDdisplayControl(1, 0, 0);
            break;
        default:
            LCDdisplayControl(0, 0, 0);
            LCDwriteMessage("+---IMPORTANT--++---MESSAGE!---+");
            sleep_ms(500);
            LCDdisplayControl(1, 0, 0);
            sleep_ms(500);
            LCDdisplayControl(0, 0, 0);
            sleep_ms(500);
            LCDdisplayControl(1, 0, 0);
            sleep_ms(500);
            LCDdisplayControl(0, 0, 0);
            LCDclear();
            LCDwriteRawMessage("+---MESSAGE:---+");
            sleep_ms(100);
            LCDdisplayControl(1, 0, 0);
            break;
    }
}

void LCDpreMessWrite(char mess[]){
    switch (LCDdisplay){
        case 1:
            if (strlen(mess) <= 16){
                LCDgoto("40");
                LCDwriteRawMessage(mess);
            } else if (strlen(mess) > 16 && strlen(mess) <= 32){
                char tmp1[23];
                strncpy(tmp1, mess, 16);
                tmp1[16] = '\0';
                LCDgoto("40");
                LCDwriteRawMessage(tmp1);
                sleep_ms(3000);
                LCDgoto("40");
                char *tmp2 = mess + 16;
                LCDwriteRawMessage(tmp2);
            }
            break;
        case 2:
            if (strlen(mess) > 16 && strlen(mess) <= 32){
                char tmp1[18];
                strncpy(tmp1, mess, 16);
                tmp1[16] = '\0';
                LCDgoto("40");
                LCDwriteRawMessage(tmp1);
                LCDgoto("14");
                char *tmp2 = mess + 16;
                LCDwriteRawMessage(tmp2);
                break;
            } else if (strlen(mess) <= 16) {
                LCDgoto("40");
                LCDwriteRawMessage(mess);
                break;
            } else if (strlen(mess) > 32 && strlen(mess) <= 64){
                char tmp1[18];
                strncpy(tmp1, mess, 16);
                tmp1[16] = '\0';
                LCDgoto("40");
                LCDwriteRawMessage(tmp1);
                LCDgoto("14");
                char *tmp2 = mess + 16;
                char tmp6[18];
                strncpy(tmp6, tmp2, 16);
                tmp6[16] = '\0';
                LCDwriteRawMessage(tmp6);
                sleep_ms(3000);
                char *tmp3 = mess + 32;
                char tmp4[23];
                strncpy(tmp4, tmp3, 16);
                tmp4[16] = '\0';
                LCDgoto("40");
                LCDwriteRawMessage(tmp4);
                char *tmp5 = tmp3 + 16;
                LCDgoto("14");
                LCDwriteRawMessage(tmp5);
            }
            break;
        case 3:
            if (strlen(mess) <= 20){
                LCDgoto("40");
                LCDwriteRawMessage(mess);
            } else if (strlen(mess) > 20 && strlen(mess) <= 40){
                char tmp1[23];
                strncpy(tmp1, mess, 20);
                tmp1[20] = '\0';
                LCDgoto("40");
                LCDwriteRawMessage(tmp1);
                sleep_ms(3000);
                LCDgoto("40");
                char *tmp2 = mess + 20;
                LCDwriteRawMessage(tmp2);
            }
            break;
        case 4:
            if (strlen(mess) > 20 && strlen(mess) <= 40){
                char tmp1[23];
                strncpy(tmp1, mess, 20);
                tmp1[20] = '\0';
                LCDgoto("40");
                LCDwriteRawMessage(tmp1);
                LCDgoto("14");
                char *tmp2 = mess + 20;
                LCDwriteRawMessage(tmp2);
                break;
            } else if (strlen(mess) <= 20) {
                LCDgoto("40");
                LCDwriteRawMessage(mess);
                break;
            } else if (strlen(mess) > 40 && strlen(mess) <= 80){
                char tmp1[23];
                strncpy(tmp1, mess, 20);
                tmp1[20] = '\0';
                LCDgoto("40");
                LCDwriteRawMessage(tmp1);
                LCDgoto("14");
                char *tmp2 = mess + 20;
                char tmp6[23];
                strncpy(tmp6, tmp2, 20);
                tmp6[20] = '\0';
                LCDwriteRawMessage(tmp6);
                sleep_ms(3000);
                char *tmp3 = mess + 40;
                char tmp4[23];
                strncpy(tmp4, tmp3, 20);
                tmp4[20] = '\0';
                LCDgoto("40");
                LCDwriteRawMessage(tmp4);
                char *tmp5 = tmp3 + 20;
                LCDgoto("14");
                LCDwriteRawMessage(tmp5);
            }
            break;
        case 5:
            if (strlen(mess) <= 40){
                LCDgoto("40");
                LCDwriteRawMessage(mess);
            } else if (strlen(mess) > 40 && strlen(mess) <= 80){
                char tmp1[43];
                strncpy(tmp1, mess, 40);
                tmp1[40] = '\0';
                LCDgoto("40");
                LCDwriteRawMessage(tmp1);
                sleep_ms(3000);
                LCDgoto("40");
                char *tmp2 = mess + 40;
                LCDwriteRawMessage(tmp2);
            }
            break;
        default:
            if (strlen(mess) <= 16){
                LCDgoto("40");
                LCDwriteRawMessage(mess);
            } else if (strlen(mess) > 16 && strlen(mess) <= 32){
                char tmp1[23];
                strncpy(tmp1, mess, 16);
                tmp1[16] = '\0';
                LCDgoto("40");
                LCDwriteRawMessage(tmp1);
                sleep_ms(3000);
                LCDgoto("40");
                char *tmp2 = mess + 16;
                LCDwriteRawMessage(tmp2);
            }
            break;
    }
}
