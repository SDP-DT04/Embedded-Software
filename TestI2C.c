/*
 * File:   TestI2C.c
 * Author: DT04
 *
 * Created on February 2, 2017, 12:35 PM
 */

#include "config.h"
#include "functions.h"
#include "xc.h"
#define FCY 60000000ULL
#include <libpic30.h>

int displaybuffer[8] = {0,0,0,0,0,0,0,0};
int i = 0;
int numbertable[] = {
  0x3F, /* 0 */
  0x06, /* 1 */
  0x5B, /* 2 */
  0x4F, /* 3 */
  0x66, /* 4 */
  0x6D, /* 5 */
  0x7D, /* 6 */
  0x07, /* 7 */
  0x7F, /* 8 */
  0x6F, /* 9 */
  0x77, /* a */
  0x7C, /* b */
  0x39, /* C */
  0x5E, /* d */
  0x79, /* E */
  0x71, /* F */
};

int main(void) 
{
    ConfigureClock();
    I2Cinit(9600);
    
/*Configure 7-Segment Display Oscillator*/    
    I2CStart();
    I2Csendbyte(0xE0);//Address E0
    I2Csendbyte(0x21);//Turn oscillator on
    I2CStop();
    __delay_ms(10);

/*Configure 7-Segment Display Blinker Speed*/    
    I2CStart();
    I2Csendbyte(0xE0);//Address E0
    I2Csendbyte(0x81);//Set blinker to off and display on
    I2CStop();
    __delay_ms(10);

/*Configure 7-Segment Display Brightness Level*/    
    I2CStart();
    I2Csendbyte(0xE0);//Address E0
    I2Csendbyte(0xE1);//Set brightness to max value
    I2CStop();
    __delay_ms(10);

    while(1)
    {
        displaybuffer[0] = numbertable[1];
        displaybuffer[1] = numbertable[4];
        displaybuffer[3] = numbertable[5];
        displaybuffer[4] = numbertable[3];

        I2CStart();
        I2Csendbyte(0xE0);//Address E0
        I2Csendbyte(0x00);//Start at address 0x00

        for (i=0; i<8; i++)
        {
            I2Csendbyte(displaybuffer[i]);
            I2Csendbyte(displaybuffer[i]);
        }
        I2CStop();
        __delay_ms(1000);
    }
    return 0;
}


//int main(void)
//{
//    ConfigureClock();
//    I2Cinit(115200);
//    while(1)
//    {
//    I2CStart();
//    I2Csendbyte(0xE0);
//    __delay_ms(1000);
//    I2Csendbyte(0x21);
//    __delay_ms(1000);
//    I2Csendbyte(0x80);
//    __delay_ms(1000);
//    I2Csendbyte(0xEF);
//    __delay_ms(1000);
//    I2CStop();
//    }
//    return 0;
//}