/*
 * File:   mc3635.c
 * Author: DT04
 *
 * Created on March 3, 2017, 1:36 PM
 */


#include "xc.h"
#include <stdint.h>
#include "XBEE.h"

void __attribute__((__interrupt__)) _SPI1Interrupt(void)
{
    mc3635_data[mc3635_w_index++] = SPI1BUF; //store new data in buffer
    
     while(!U1STAbits.TRMT);
            U1TXREG = mc3635_data[mc3635_w_index-1];
    
    if (mc3635_w_index == MC3635_BUF_LEN)//wrap index?
        mc3635_w_index = 0; 
    
    IFS0bits.SPI1EIF = 0; //clear the interrupt flag
}

void mc3635_init()
{
    IFS0bits.SPI1EIF = 0; //clear the interrupt flag
    IEC0bits.SPI1EIE = 0; //disable the interrupt
    
    SPI1STATbits.SISEL = 0b011; //interrupt when the receive buffer is full
    SPI1CON1bits.DISSCK = 0; //internal serial clock enabled
    SPI1CON1bits.DISSDO = 0; //SD0x pin is controlled by module
    SPI1CON1bits.MODE16 = 0; //communication is 16 bits
    SPI1CON1bits.MSTEN = 1; //master mode enable
    SPI1CON1bits.SMP = 0; //input sampled at the middle of data output time
    SPI1CON1bits.CKE = 1; //output data changes on idle clock state to active clock state
    SPI1CON1bits.CKP = 0; //idle state for clock is low level    
    SPI1STATbits.SPIEN = 1; //enable SPI
    
    IFS0bits.SPI1EIF = 0; //clear the interrupt flag
    IEC0bits.SPI1EIE = 1; //enable the interrupt
}

void mc3635_send(uint8_t x)
{
    while(!U1STAbits.TRMT);
            U1TXREG = 'G';
    while (SPI1STATbits.SPITBF); //wait for transmit buffer to be empty
    SPI1BUF = x; //load the SPI buffer
    
        while(!U1STAbits.TRMT);
            U1TXREG = 'H';
}

void mc3635_read_z_low()
{
    mc3635_send(0x86);
}

void mc3635_read_z_high()
{
    mc3635_send(0x87);
}

void mc3635_tasks()
{
    
}