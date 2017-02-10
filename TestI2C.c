/*
 * File:   TestI2C.c
 * Author: DT04
 *
 * Created on February 2, 2017, 12:35 PM
 */

#include "config.h"
#include "functions.h"
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "xc.h"
//#define FCY 8000000ULL
//#include <libpic30.h>

#define HT16K33 0xE0 // I2C bus address for Ht16K33 backpack
#define HT16K33_ON 0x21 // turn device oscillator on
#define HT16K33_STANDBY 0x20 // turn device oscillator off
#define HT16K33_DISPLAYON 0x81 // turn on output pins
#define HT16K33_DISPLAYOFF 0x80 // turn off output pins
#define HT16K33_BLINKON 0x85 // blink rate 1 Hz (-2 for 2 Hz)
#define HT16K33_BLINKOFF 0x81 // same as display on
#define HT16K33_DIM 0xE0 // add level (15=max) to byte

typedef uint8_t byte;

static const byte numberTable[] = // convert number to lit-segments
{
 0x3F, // 0
 0x06, // 1
 0x5B, // 2
 0x4F, // 3
 0x66, // 4
 0x6D, // 5
 0x7D, // 6
 0x07, // 7
 0x7F, // 8
 0x6F, // 9
 0x77, // A
 0x7C, // b
 0x39, // C
 0x5E, // d
 0x79, // E
 0x71, // F
 0x00, //<blank>
};

void I2C_Init(int BRG)
{
    I2C1BRG = BRG;
    I2C1CONbits.I2CEN = 1;
}

void I2C_Start (byte slaveAddr)
{
    I2C1CONbits.SEN = 1;
    while(I2C1STATbits.TBF);
    I2C1TRN = 0xE0;
}
void I2C_Stop ()
{
    I2C1CONbits.PEN = 1;
}

void I2C_Write (byte data) // sends a data byte to slave
{
    while(I2C1STATbits.TBF)
    I2C1TRN = data; // load data to be sent
}

void I2C_WriteByte(byte busAddr, byte data)
{
 I2C_Start(busAddr); // send bus address
 I2C_Write(data); // then send the data byte
 I2C_Stop();
}

void SS_Init()
{
 I2C_WriteByte(HT16K33,HT16K33_ON); // turn on device oscillator
 I2C_WriteByte(HT16K33,HT16K33_DISPLAYON); // turn on display, no blink
 I2C_WriteByte(HT16K33,HT16K33_DIM + 15); // set max brightness
}

int main(void)
{
    __delay_ms(1000);
    while(1)
    {
        I2C_Init(50); // set I2C clock frequency
        SS_Init(); // initialize HT16K33 LED controller
    }
    
    return 0;
}