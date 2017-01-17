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

int main(void)
{
/*---------------Configure GPIO pins as either Analog pins or Digital pins----*/
    ANSELAbits.ANSA12=0;//Analog Select to off
    TRISAbits.TRISA12 = INPUT;//set port A12 as an input
    TRISAbits.TRISA0 = OUTPUT;//set port A0 as an output
    PORTAbits.RA12 = LOW;//Set initial state to LOW
    PORTAbits.RA0 = LOW;//Set initial state to LOW    
    SetupClock();
    while(1)
    {
        PORTAbits.RA0 = HIGH;
        __delay_ms(1000);
        PORTAbits.RA0 = LOW;
        __delay_ms(1000);
    }
    return 0;
}
    

