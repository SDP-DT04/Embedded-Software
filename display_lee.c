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
//#define FCY 8000000ULL
#include <libpic30.h>

static const unsigned char numberTable[] = // convert number to lit-segments
{
 0x3F, // 0
 0x06, // 1
 0x5B, // 2
 0x4F, // 3
 0x66, // 4
 0x6D, // 5
 0x7D, // 6
 0x07, // 7
 0x7F, // 8
 0x6F, // 9
 0x77, // A
 0x7C, // b
 0x39, // C
 0x5E, // d
 0x79, // E
 0x71, // F
 0x00, //<blank>
};

enum I2C_Config_State{
    INIT,
    SEND_START,
    SEND_ADDR,
    SEND_BYTE,
    SEND_STOP,
    NEXT_COMMAND,
    IDLE
};

enum I2C_Display_State{
    WAIT,
    SEND_START_D,
    SEND_ADDR_D,
    SEND_RAM,
    SEND_BYTE_D,
    SEND_STOP_D
};

unsigned char* display_commands; 

unsigned char beef_commands[] = {
    0x7C,
    0x79,
    0x00,
    0x79,
    0x71,
    0x99
};

unsigned char nums[] = {
    1,
    2,
    16,
    3,
    4,
    0x99
};

unsigned char lee_commands[] = {
    0x38,
    0x79,
    0x00,
    0x79,
    0x00,
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
bool resend = true; 

enum I2C_Display_State _display_state = WAIT; 
enum I2C_Config_State _config_state = INIT; 
bool new_data = false;
void config_tasks()
{  
    if (I2C1STATbits.TBF)
        return;
    
    switch (_config_state)
    {
        case INIT:
        {
            i = 0;
            // config
            I2C1BRG = 50;
         
            I2C1CONbits.I2CEN = 1;
            _config_state = SEND_START;
            break;
        }
        case SEND_START:
        {
            // send start
            I2C1CONbits.SEN = 1;
            _config_state = SEND_ADDR; 
            break;
        }
        case SEND_ADDR:
        {
            if (I2C1CONbits.SEN == 0)
            {                
                I2C1TRN = 0xE0;
                _config_state = SEND_BYTE;
            }
            break;
        }
        case SEND_BYTE:
        {   
            if (I2C1STATbits.TRSTAT == 0)
            {
                if (I2C1STATbits.ACKSTAT == 0)
                {
                    // we have address ack
                    //data = *cmd;
                    I2C1TRN = config_commands[i];
                    _config_state = SEND_STOP;
                }
                else
                {
                    _config_state = SEND_START; 
                    __delay_ms(100);
                }
            }
            break;
        }
        case SEND_STOP:
        {
            if (I2C1STATbits.TRSTAT == 0)
            {
                if (I2C1STATbits.ACKSTAT == 0)
                {
                    I2C1CONbits.PEN = 1;
                    _config_state = NEXT_COMMAND; 
                }
                else
                {
                    _config_state = SEND_START;
                     __delay_ms(100);
                }
            }
            break;
        }
        case NEXT_COMMAND:
        {
            if (I2C1CONbits.PEN == 0)
            {
                i++; 
                if (config_commands[i] == 0x99)
                {
                    _config_state = IDLE;
                }
                else
                {_config_state = SEND_START;}
                __delay_ms(100);
            }   
            break; 
        }
        case IDLE:
        {
            display_commands = lee_commands;
            new_data = true;
        }
    }
}

void display_time(int mstime)
{
    nums[0] = mstime / 1000;
    mstime = mstime % 1000; 
    nums[1] = mstime / 100;
    nums[2] = 16;
    mstime = mstime % 100; 
    nums[3] = mstime / 10; 
    mstime = mstime % 10; 
    nums[4] = mstime; 
    
    display_commands = nums; 
    new_data = true; 
}

void display_tasks()
{
    switch(_display_state)
    {
        case WAIT:
        {
            if (new_data)
            {
                i = 0; 
                new_data = false; 
                _display_state = SEND_START_D; 
            }
            break; 
        }
        case SEND_START_D:
        {
            // send start
            I2C1CONbits.SEN = 1;
            _display_state = SEND_ADDR_D; 
            
            break; 
        }
        case SEND_ADDR_D:
        {
            if (I2C1CONbits.SEN == 0)
            {                
                I2C1TRN = 0xE0;
                _display_state = SEND_RAM;
            }
            break;
        }
        case SEND_RAM:
        {
            if (I2C1STATbits.TRSTAT == 0)
            {
                if (I2C1STATbits.ACKSTAT == 0)
                {
                    // we have address ack
                    //data = *cmd;
                    I2C1TRN = 0x00;
                    _display_state = SEND_BYTE_D;
                }
                else
                {
                    _display_state = SEND_START_D; 
                }
            }
            break; 
        }
        case SEND_BYTE_D:
        {
            if (I2C1STATbits.TRSTAT == 0)
            {
                if (I2C1STATbits.ACKSTAT == 0)
                {
                    // we have address ack
                    //data = *cmd;
                    I2C1TRN = display_commands[i];
                    if (!resend)
                    {
                        ++i;
                    }
                    resend = !resend; 
                    if (display_commands[i] == 0x99)
                    {
                       _display_state = SEND_STOP_D;
                    }
                    else
                    {
                        _display_state = SEND_BYTE_D;
                    }   
                }
                else
                {
                    if (i == 0)
                        _display_state = SEND_RAM;
                    else
                        _display_state = SEND_BYTE_D;
                }
            }
            break;
        }
        case SEND_STOP_D:
        {
            if (I2C1STATbits.TRSTAT == 0)
            {
                if (I2C1STATbits.ACKSTAT == 0)
                {
                    I2C1CONbits.PEN = 1;
                    _display_state = WAIT;
                }
                else
                {
                    --i; 
                    resend = !resend; 
                    _display_state = SEND_BYTE_D;
                }
            }
            break;
        }
    }
}

//int dSec = 0;
//void  _ISR  _T3Interrupt(void)
//{
////    dSec++;
////    display_time(dSec);
////    
////    _T3IF = 0;//clear  the  flag
//
//}

void main(void)
{
    RCONbits.SWDTEN = 0;
     TRISAbits.TRISA0 = 0;
    ConfigureClockSlow();
     PORTAbits.RA0 = 1; 
    __delay_ms(100);
     PORTAbits.RA0 = 0; 
    //__delay_ms(100);
     
//    _T3IP = 4;//interrupt setup
//    TMR3 = 0;//set timer 1 to zero
//    T3CON = 0x8030; //
//    PR3 = 2343;//creates one 10 millisecond timer
//    _T3IF = 0;
   // _T3IE = 1;
    
    while(1)
    {
     config_tasks();
     display_tasks();
    }

}

