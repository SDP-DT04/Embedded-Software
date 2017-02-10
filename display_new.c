/*
 * File:   I2C_State_Machine.c
 * Author: DT04
 *
 * Created on February 6, 2017, 12:50 PM
 */

//CARL

#include "config.h"
#include "functions.h"
#include "xc.h"
#include "stdbool.h"
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

unsigned char dispaly_commands[] = {
    0x7C,
    0x7C,
    0x79,
    0x79,
    0x00,
    0x00,
    0x79,
    0x79,
    0x71,
    0x71,
    0x99
    
};

unsigned char config_commands[] = {
    0x21,
    0x81,
    0xEF,
    0x99
};

unsigned char i = 0; 
unsigned char data = 0;

static enum I2C_State _state = INIT; 
static bool is_setup = true;
void config_tasks()
{  
    if (I2C1STATbits.TBF)
        return;
    
    switch (_state)
    {
        case INIT:
        {
            i = 0;
            // config
            I2C1BRG = 50;
            I2C1CONbits.I2CEN = 1;
            _state = SEND_START;
            break;
        }
        case SEND_START:
        {
            // send start
            I2C1CONbits.SEN = 1;
            _state = SEND_ADDR; 
            break;
        }
        case SEND_ADDR:
        {
            if (I2C1CONbits.SEN == 0)
            {                
                I2C1TRN = 0xE0;
                _state = SEND_BYTE;
            }
            break;
        }
        case SEND_BYTE:
        {   
            if (I2C1STATbits.ACKSTAT == 0)
            {
                // we have address ack
                //data = *cmd;
                I2C1TRN = config_commands[i];
                _state = SEND_STOP;
            }
            break;
        }
        case SEND_STOP:
        {
            if (I2C1STATbits.ACKSTAT == 0)
            {
                I2C1CONbits.PEN = 1;
                _state = NEXT_COMMAND; 
            }
            break;
        }
        case NEXT_COMMAND:
        {
            if (I2C1CONbits.PEN == 0)
            {
                i++; 
                if (config_commands[i] == 0x99)
                    _state = IDLE;
                
                else
                {_state = SEND_START;}
            }   
            break; 
        }
        case IDLE:
        {
            
        }
    }
}

void display_tasks()
{
    
    
}

void main(void)
{
    ConfigureClockSlow();
    __delay_ms(1000);
    //__delay_ms(100);
    while(1)
    {
     display_tasks();
    }


//    I2C1BRG = 50;
//    I2C1CONbits.I2CEN = 1;
//    while (1)
//    {
//        PORTAbits.RA0 = 1;
//        I2C1CONbits.SEN = 1; //Start bit
//        __delay_ms(10);
//        I2C1TRN = 0xE0; //Address display
//        if (I2C1STATbits.ACKSTAT == 0)
//        {
//            I2C1TRN = 0x21; //Turn oscillator on
//        }
//        __delay_ms(10);
//        I2C1CONbits.PEN = 1; //Stop bit
//        __delay_ms(100);
//        
//        I2C1CONbits.SEN = 1; //Start bit
//        __delay_ms(100);
//        I2C1TRN = 0xE0; //Address display
//        if (I2C1STATbits.ACKSTAT == 0)
//        {
//            I2C1TRN = 0x81; //Turn display on, set no blink
//        }
//        __delay_ms(10);
//        I2C1CONbits.PEN = 1; //Stop bit
//        __delay_ms(100);
//        
//        I2C1CONbits.SEN = 1; //Start bit
//        __delay_ms(100);
//        I2C1TRN = 0xE0; //Address display
//        if (I2C1STATbits.ACKSTAT == 0)
//        {
//            I2C1TRN = 0xEF; //Set brightness level
//        }
//        __delay_ms(10);
//        I2C1CONbits.PEN = 1; //Stop bit
//        __delay_ms(100);
//        
//        I2C1CONbits.SEN = 1; //Start bit
//        __delay_ms(100);
//        I2C1TRN = 0xE0; //Address display
//        __delay_ms(10);
//        I2C1TRN = 0x00; //Address RAM location
//        __delay_ms(10);
//        I2C1TRN = 0x7C; //Send first character
//        __delay_ms(10);
//        I2C1TRN = 0x7C; //Send first character
//        __delay_ms(10);
//        I2C1TRN = 0x79; //Send second character
//        __delay_ms(10);
//        I2C1TRN = 0x79; //Send second character
//        __delay_ms(10);
//        I2C1TRN = 0x00; //Send decimal places
//        __delay_ms(10);
//        I2C1TRN = 0x00; //Send decimal places
//        __delay_ms(10);
//        I2C1TRN = 0x79; //Send third character
//        __delay_ms(10);
//        I2C1TRN = 0x79; //Send third character
//        __delay_ms(10);
//        I2C1TRN = 0x71; //Send fourth character
//        __delay_ms(10);
//        I2C1TRN = 0x71; //Send fourth character
//        __delay_ms(10);
//        I2C1CONbits.PEN = 1; //Stop bit
//        __delay_ms(100);
//        PORTAbits.RA0 = 0;
//    }
}
