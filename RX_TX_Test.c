/*
 * File:   RX&TX_Test.c
 * Author: DT04
 *
 * Created on February 17, 2017, 12:48 PM
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
int p = 0, j = 0, k = 0, m = 0, n = 0, c=0, success=0;
unsigned char byteRead;
const int tagLen = 16;
const int idLen = 13; //idLen = 13  because 12 data plus NULL
const int kTags = 4; //total number of tags
char nTag[12];
char oTag[12];
char knownTags[12] = {"82003BE82372"};
char newTag[16]={"0000000000000000"}; //idLen = 13  because 12 data plus NULL
char tagData[12]={"000000000000"};
char test[12] = {"82003BE82372"};

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
    U1MODEbits.UARTEN = 1; //Enable UART
    IEC0bits.U1RXIE = 1; //Enable RX UART interrupt 
    U1STAbits.UTXEN = 1;//Set TX to Enable
    U1STAbits.URXISEL = 0b00; //load 1 bytes in U1RXREG
    
    RPINR18bits.U1RXR = 0b0100111; //Set pin 46 (RP39) to U1RX pin
    RPOR5bits.RP54R = 0b000001; //Set pin 50 (RP54) as U1TX pin
    
    PORTDbits.RD8 = 1; //Set Pin high for led

    while(1){
//        if(i>12){
//            while(!U1STAbits.TRMT); //wait till able to transmit
//            U1TXREG=0x0A;
//            i=0;
//        }
        
//        if(U1STAbits.URXDA){
//            byteRead = U1RXREG;
//            __delay_ms(3);
//            
//            U1TXREG = byteRead;
//
//            if(k<12){
//                if (byteRead != 2 && byteRead!= 13 && byteRead != 10 && byteRead != 3)
//                {
//                    tagData[k] = byteRead;
//                    k++;
//                }
//            }
//            else{
//                success=1;
//                k=0;
//            }
//            if(success==1){
//                for(i=0; i<12; i++){
//                    U1TXREG = tagData[i];
//                    __delay_ms(2);
//        
//                     //U1TXREG = 0x0A;
//                }
//                U1TXREG = 0x0A;//new line
//                success=0;
//            } 
//        }
    }
    return 0;
}

void __attribute__((__interrupt__)) _U1RXInterrupt(void)
{
    static int i=0;
    while(U1STAbits.URXDA){
        byteRead=U1RXREG;       //Read in data from register
        while(!U1STAbits.TRMT); //wait till able to transmit 
        U1TXREG=byteRead;       //Transmit
        while(!U1STAbits.TRMT); //wait till able to transmit 
        newTag[i]=byteRead;
        i++;
    }

    IFS0bits.U1RXIF = 0;    //Clear Flag
}
            
