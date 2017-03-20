/*
 * File:   mc3635.c
 * Author: DT04
 *
 * Created on March 3, 2017, 1:36 PM
 */


#include "xc.h"
#include <stdint.h>
#include "XBEE.h"

#define FCY 60000000ULL
#include <libpic30.h>

void __attribute__((__interrupt__)) _SPI1Interrupt(void)
{
    mc3635_data[mc3635_w_index++] = SPI1BUF; //store new data in buffer
    
     while(!U1STAbits.TRMT);
            U1TXREG = mc3635_data[mc3635_w_index-1];
    
    if (mc3635_w_index == MC3635_BUF_LEN)//wrap index?
        mc3635_w_index = 0; 
    
    IFS0bits.SPI1EIF = 0; //clear the interrupt flag
}

uint16_t mc3635_send(uint16_t x)
{     
    while (SPI1STATbits.SPITBF);
    PORTBbits.RB0 = 0; 
    SPI1BUF = x; //load the SPI buffer
    //wait for receive buffer to be full
    while (!SPI1STATbits.SPIRBF);
    uint16_t y = SPI1BUF; 
    
         while(!U1STAbits.TRMT);
            U1TXREG = 'C';
    
    PORTBbits.RB0 = 1;
    return y; 
}

void mc3635_init()
{
    ANSELBbits.ANSB0 = 0; 
    
    // configure SPI input pins
//    RPINR22bits.SCK2INR = 0b1100001; 
//    RPINR22bits.SDI2R = 0b1110111; 
//    RPINR23bits.SS2R = 0b1110110; 
//    
//    // configure SPI output pins
//    RPOR4bits.RP42R = 0b001000; 
//    RPOR7bits.RP97R = 0b001001;
//    RPOR8bits.RP118R = 0b001010;
    SPI1BUF = 0;
    IFS0bits.SPI1EIF = 0; //clear the interrupt flag
    IEC0bits.SPI1EIE = 0; //disable the interrupt
    
    SPI1CON1bits.PPRE = 0b01; 
    SPI1CON1bits.SPRE = 0b110; //SCK at  1.875MHz
    
    //SPI1STATbits.SISEL = 0b011; //interrupt when the receive buffer is full
    SPI1CON1bits.DISSCK = 0; //internal serial clock enabled
    SPI1CON1bits.DISSDO = 0; //SD0x pin is controlled by module
    SPI1CON1bits.MODE16 = 1; //communication is 16 bits
    SPI1CON1bits.MSTEN = 1; //master mode enable
    SPI1CON1bits.SMP = 0; //input sampled at the middle of data output time
    SPI1CON1bits.CKE = 0; //output data changes on idle clock state to active clock state
    SPI1CON1bits.CKP = 1; //idle state for clock is low level    
    SPI1STATbits.SPIROV = 0; //clear the overflow register 
    SPI1STATbits.SPIEN = 1; //enable SPI
    
    
    TRISBbits.TRISB0 = 0; 
    PORTBbits.RB0 = 1; 
    
    //mc3635_enable_spi();
    
   // IFS2bits.SPI2EIF = 0; //clear the interrupt flag
   // IEC2bits.SPI2EIE = 1; //enable the interrupt
    mc3635_send(0x4F42); 
    mc3635_send(0x4D80); //set feature 1 register - enable spi mode
    mc3635_send(0x5108); //set rate register - rate to 100Hz
    mc3635_send(0x5005); //set status 1 register - accelerometer in "wake" mode
    mc3635_send(0x5505); //set range and resolution - 14bits, 2g
}

void mc3635_read_z_low()
{    
    mc3635_send(0xC700); //read x_out msb
    mc3635_send(0xC600); //read x_out lsb
}

void mc3635_read_z_high()
{
    mc3635_send(0x87);
}

void mc3635_enable_spi()
{
    mc3635_send(0x4D80);
}

//void mc3635_set

void mc3635_tasks()
{
    
}