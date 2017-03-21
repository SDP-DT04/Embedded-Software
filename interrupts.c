/*
 * File:   interrupts.c
 * Author: DT04
 *
 * Created on March 20, 2017, 1:58 PM
 */

#include "xc.h"
#include <stdbool.h>
#include "XBEE.h"
#include "mc3635.h"
#include "display.h"

static int error_counter = 0; 
static int dSec = 0;
static bool is_swimming = false;
/**
 * Timer 1 interrupt service routine
 * Used for display and accelerometer
 */
void _ISR __attribute__((auto_psv)) _T1Interrupt(void)
{
    if (is_swimming == false)
    {
        if (PORTCbits.RC13 == 1)
        {
            XBEE_begin_transmit(); //start xbee transmit
            is_swimming = true;
            TMR1=0;
            dSec=0;
            
            mc3635_read_z_low();
        }
        
        else if (PORTCbits.RC13 == 0)
        {}
    }
    
    else if(is_swimming == true)
    {
        if (PORTCbits.RC13 == 1)
        {
            if (dSec<9999)
            {dSec++;}
            else 
            {dSec = 0;}
            
            if (!DISPLAY_is_displaying())
            {
                DISPLAY_time(dSec);
                error_counter = 0; 
            }
            else
            {
                error_counter++;
            }
                
            if (error_counter > 5)
            {
                DISPLAY_error();
            }
        }
        
        else if (PORTCbits.RC13 == 0)
        {
            XBEE_end_transmit();     
            is_swimming = false;
            TMR1=0;
        }
    }
 _T1IF = 0;//clear  the  flag
}

/**
 * UART1 Interrupt service routine
 * Used for RFID
 */
void __attribute__((__interrupt__)) _U1RXInterrupt(void)
{
   static uint8_t inByte; 
   static uint8_t i; 
   
   while(U1STAbits.URXDA) //while RX data is available 
    {
        inByte=U1RXREG;       //Read in data from register
        while(!U1STAbits.TRMT); //Wait until able to transmit 
      //  U1TXREG = newTag[i]; //Transmit
    
//        i++;
//        if (i == 16)
//        {
//            i = 0;
//        }
    }
    IFS0bits.U1RXIF = 0;    //Clear Flag
}