/*
 * File:   I2C_State_Machine.c
 * Author: DT04
 *
 * Created on February 6, 2017, 12:50 PM
 */


#include "config.h"
#include "functions.h"
#include "xc.h"
#define FCY 8000000ULL
#include <libpic30.h>

enum I2C_State{
    INIT,
    SEND_START,
    SEND_ADDR,
    SEND_BYTE,
    SEND_STOP,
    NEXT_COMMAND,
    IDLE
};

unsigned char commands[] = {
    0x21,
    0x81,
    0xE1,
    0x00
};

unsigned char* cmd = commands; 
unsigned char data = 0;

enum I2C_State _state = INIT; 

void display_tasks()
{  
    switch (_state)
    {
        case INIT:
        {
            // config
            I2C2BRG = 50;
            I2C2CONbits.I2CEN = 1;
            TRISAbits.TRISA0 = 0;
            _state = SEND_START;
            break;
        }
        case SEND_START:
        {
            // send start
            I2C2CONbits.SEN = 1;
            _state = SEND_ADDR; 
            break;
        }
        case SEND_ADDR:
        {
            if (I2C2CONbits.SEN == 0)
            {
                 while(I2C2STATbits.TBF);
                I2C2TRN = 0xE0;
                _state = SEND_BYTE;
            }
            break;
        }
        case SEND_BYTE:
        {   
            if (I2C2STATbits.ACKSTAT == 0)
            {
                // we have address ack
                data = *cmd;
                while(I2C2STATbits.TBF);
                I2C2TRN = *cmd;
                _state = SEND_STOP;
            }
            break;
        }
        case SEND_STOP:
        {
            if (I2C2STATbits.ACKSTAT == 0)
            {
                I2C2CONbits.PEN = 1;
                _state = NEXT_COMMAND; 
            }
            break;
        }
        case NEXT_COMMAND:
        {
            if (I2C2CONbits.PEN == 0)
            {
                cmd++; 
                if (*cmd == 0x00)
                    _state = IDLE;
                
                _state = SEND_START;
            }   
            break; 
        }
        case IDLE:
        {
            
        }
    }
}

void main(void)
{
    ConfigureClockSlow();
    __delay_ms(1000);
    int i = 4; 
    while (1)
    {
        display_tasks();
        __delay_ms(100);
    }
}
