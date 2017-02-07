/*
 * File:   timertest.c
 * Author: DT04
 *
 * Created on January 11, 2017, 12:10 PM
 */

#include "config.h"
#include "functions.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <p33EP256MC506.h>
#define FCY 60000000ULL
#include <libpic30.h>

#define OUTPUT  0b0;
#define INPUT 0b1;
#define HIGH 0b1;
#define LOW 0b0;
#define OFF 0b0;
#define ON 0b1;


int  dSec = 0, Sec = 0; // two  global  variables
int Restart=0, Start=0, Finish=0;
char c[4]="0000";
void  _ISR  _T3Interrupt(void)
{
    sprintf(c,"%04d",Sec);
    if(Start==0){}
    else if(Start==1)
    {
        Sec++;
        display(c, 16);
    }

    
    _T3IF = 0;//clear  the  flag

}

int main(void)
{
    
/*---------------Configure Timer3 as an Interrupt Source----------------------*/    
    _T3IP = 4;//interrupt setup
    TMR3 = 0;//set timer 1 to zero
    T3CON = 0x8030; //
    PR3 = 2343;//creates one 10 millisecond timer
    _T3IF = 0;
    _T3IE = 1;

/*---------------Configure GPIO pins as either Analog pins or Digital pins----*/    
    ANSELAbits.ANSA12=0;//Analog Select to off
    TRISAbits.TRISA12 = INPUT;//set port A12 as an input
    TRISAbits.TRISA0 = OUTPUT;//set port A0 as an output
    PORTAbits.RA12 = LOW;//Set initial state to LOW
    PORTAbits.RA0 = LOW;//Set initial state to LOW

    
    int State=0;
    
    I2Cinit(299);
    ConfigureClock();
    while(1)
    {
        if(Start==0)
        {
            if(PORTAbits.RA12 == 1)
            {
                Start=1;
                TMR3=0;
                Sec=0;
            }
            else{}
        }
    
        else if(Start==1)
        {
            if(PORTAbits.RA12 == 0)
            {
                Start=0;
                State=1;
                TMR3=0;
            }
            else{}    
        }
    }
    return 0;
}