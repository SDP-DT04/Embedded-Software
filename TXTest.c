/*
 * File:   TXTest.c
 * Author: DT04
 *
 * Created on February 17, 2017, 12:33 PM
 */
#include "config.h"
#include "functions.h"
#include <xc.h>
#include  <stdbool.h>
#include <p33EP256MC506.h>
#include <string.h>
#define FCY 60000000ULL
//#define FCY 8000000ULL
#include <libpic30.h>

char ReceivedChar[16] = {"0000000000000000"};
int i = 0, j = 0, k = 0, m = 0, n = 0, c=0;
const int tagLen = 16;
const int idLen = 13; //idLen = 13  because 12 data plus NULL
const int kTags = 4; //total number of tags
char nTag[12];
char oTag[12];
char knownTags[12] = {"82003BE82372"};

char newTag[16]={"0000000000000000"}; //idLen = 13  because 12 data plus NULL
char tagData[12]={"000000000000"};
char test[12] = {"82003BE82372"};
//test[0] = 0x02;
//test[13] = 0x0D;
//test[14] = 0x0A;
//test[15] = 0x03;


int main(void)
{
    ConfigureClock();
    TRISAbits.TRISA0 = 0;
    TRISDbits.TRISD8 = 0;
    U1MODEbits.STSEL = 0; //1-stop bit
    U1MODEbits.PDSEL = 0; //No parity, 8-bit data
    U1MODEbits.ABAUD = 0; //Auto baud rate is disabled
    U1MODEbits.BRGH = 0; //Standard baud rate
    
    U1BRG = 390; //set baud rate register
    
    U1STAbits.URXISEL = 0b11; //load 4 bytes in U1RXREG
    
    U1MODEbits.UARTEN = 1; //Enable UART
    
    U1STAbits.UTXEN = 1;//Set TX to Enable
    
    RPINR18bits.U1RXR = 0b0100111; //Set pin 46 (RP39) to U1RX pin
    RPOR5bits.RP54R = 0b000001; //Set pin 50 (RP54) as U1TX pin
    PORTDbits.RD8 = 1;

    while(1){
        for(i=0; i<12; i++){
        U1TXREG = test[i];
        __delay_ms(2);
        
        //U1TXREG = 0x0A;
        }
        U1TXREG = 0x0A;
    }


    
}

