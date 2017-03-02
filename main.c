/*
 * File:   I2C_State_Machine.c
 * Author: DT04
 *
 * Created on February 6, 2017, 12:50 PM
 */

//CARL

#include "config.h"
#include "display.h"
#include "functions.h"
#include "xc.h"
#include "accelData.h"
#include "XBEE.h"
#include "stdbool.h"
#define FCY 60000000ULL
//#define FCY 8000000ULL
#include <libpic30.h>

char ReceivedChar[16] = {"0000000000000000"};
int p = 0, j = 0, k = 0, m = 0, n = 0, c=0, success=0;
unsigned char byteRead;
const int tagLen = 16;
const int idLen = 13; //idLen = 13  because 12 data plus NULL
const int kTags = 4; //total number of tags
char nTag[12];
char oTag[12];
char knownTags[12] = {"82003BE82372"};

 //={"0000000000000000"}; //idLen = 13  because 12 data plus NULL
char tagData[12]={"000000000000"};
char test[12] = {"82003BE82372"};

int main(void)
{
    ConfigureClock(); //Configure Clock to 60[MHz]
    __delay_ms(1100);
    TRISAbits.TRISA0 = 0; //Set pin 13 (RA0) as output
    TRISDbits.TRISD8 = 0; //Set pin 42 (RD8) as output
    ANSELAbits.ANSA12=0; //Set pin 11 (RA12) as digital pin
    TRISCbits.TRISC13 = 0b1; //Set pin 47 (RC13) as input
    
    U1MODEbits.STSEL = 0; //1-stop bit
    U1MODEbits.PDSEL = 0; //No parity, 8-bit data
    U1MODEbits.ABAUD = 0; //Auto baud rate is disabled
    U1MODEbits.BRGH = 0; //Standard baud rate
    U1BRG = 390; //Set baud rate register
    U1MODEbits.UARTEN = 1; //Enable UART
    IEC0bits.U1RXIE = 1; //Enable RX UART interrupt 
    U1STAbits.UTXEN = 1;//Set TX to Enable
    U1STAbits.URXISEL = 0b00; //Load 1 bytes in U1RXREG
    //RPINR18bits.U1RXR = 0b0110111; //Set pin 51 (RP55) to U1RX pin
    RPINR18bits.U1RXR = 0b0100111; //Set pin 46 (RP39) to U1RX
    RPOR5bits.RP54R = 0b000001; //Set pin 50 (RP54) as U1TX pin
    
    U2MODEbits.STSEL = 0; //1-stop bit
    U2MODEbits.PDSEL = 0; //No parity, 8-bit data
    U2MODEbits.ABAUD = 0; //Auto baud rate is disabled
    U2MODEbits.BRGH = 0; //Standard baud rate
    U2BRG = 390; //Set baud rate register
    U2MODEbits.UARTEN = 1; //Enable UART
    //IEC1bits.U2RXIE = 1;
    U2STAbits.UTXEN = 1;//Set TX to Enable
    U2STAbits.URXISEL = 0b00; //Load 1 bytes in U1RXREG
    RPINR19bits.U2RXR = 0b0101100; //Set pin 62(RPI44) to U2RX pin
    RPOR4bits.RP43R = 0b000011; //Set pin 61 (RP43) to U2TX pin
    
    PORTDbits.RD8 = 1; //Set pin 42 (RD8) high for LED
    __delay_ms(1000);
   
    
    _T1IP = 4; //Interrupt setup
    TMR1 = 0; //Set timer 1 to zero
    T1CON = 0x8030; //Enable timer 1 and ser prescalar to 256 
    PR1 = 2360;//creates 10[ms] timer for 60[MHz]
    //PR1= 313; //creates 10[ms] timer for 8[MHz]
    _T1IF = 0;
    _T1IE = 1;
    
    while(1)
    {
        config_tasks();
        display_tasks();
        xbee_tasks();
    }
    return 0;
}

void __attribute__((__interrupt__)) _U1RXInterrupt(void)
{
    U1TXREG = 'p';
//    static int i=0;
    while(U1STAbits.URXDA)
    {
        byteRead=U1RXREG;       //Read in data from register
        //while(!U1STAbits.TRMT); //Wait until able to transmit 
        //newTag[i]=byteRead;
        while(!U1STAbits.TRMT); //Wait until able to transmit 
      //  U1TXREG = newTag[i]; //Transmit
        U1TXREG = 'p';
//        i++;
//        if (i == 16)
//        {
//            i = 0;
//        }
    }
    IFS0bits.U1RXIF = 0;    //Clear Flag
}

//void _ISR __attribute__((auto_psv))  _T1Interrupt(void)
//{
//    _T1IF = 0;//clear  the  flag
//}
