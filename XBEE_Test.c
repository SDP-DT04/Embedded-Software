/*
 * File:   XBEE_Test.c
 * Author: DT04
 *
 * Created on February 10, 2017, 3:18 PM
 */


#include "config.h"
#include "functions.h"
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "xc.h"

#define RTS2 _RC12   //output, XBEE on UART2
#define CTS2 _RC13  //input, XBEE on UART2


void InitU2(void);
char putU2(char c);
char getU2(void);


int main(void) {
   // RPINR18 = 0x0064;
    int i=0;
    char message[5]={"Hello"};
    InitU2();
    __delay_ms(200);
    while (1){
    
        for(i=0;i<5;i++){
            putU2(message[i]);
        }
        __delay_ms(500);
    }
    
    return 0;
}

void InitU2(void){
    U2BRG = 415; //baud-9600, BRGH=1
    U2MODE=0x8008; //8N1
    U2STA = 0x400;//Enable Transmission
    TRISAbits.TRISA0 = 0;
    TRISCbits.TRISC2 = 1;//enable RTS, output
    RTS2 = 1;//default status, not ready to send
}

char putU2(char c){
    while(CTS2); //wait for !CTS active low
    while (U1STAbits.UTXBF); //wait while tx buffer is full
    U2TXREG = c; //send the char
    return c;    
}

char getU2(void){
    RTS2=0; //telling the other side !RTS
    while(!U1STAbits.URXDA);//wait
    RTS2=1; //telling the other side RTS
    return U2RXREG; //from recieving buffer
    
}
