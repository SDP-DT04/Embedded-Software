/*
 * File:   I2C_State_Machine.c
 * Author: DT04
 *
 * Created on February 6, 2017, 12:50 PM
 */


#include <stdbool.h>
#include "display.h"
#include "XBEE.h"
#include "mc3635.h"

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
 0x02, //Center Colon
 0x37  // n
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

unsigned char nums[] = {
    1,
    2,
    1,
    3,
    4,
    0x99
};

unsigned char config_commands[] = {
    0x21,
    0x81,
    0xE2,
    0x99
};

static unsigned char i = 0; 
unsigned char data = 0;
bool resend = true; 
bool zero_set = false;
bool new_data = false;
bool is_displaying = false;

enum I2C_Display_State _display_state = WAIT; 
enum I2C_Config_State _config_state = INIT; 

bool DISPLAY_config_done( void )
{
    return zero_set; 
}

void DISPLAY_blank()
{
    nums[0] = 16; 
    nums[1] = 16;
    nums[2] = 16; 
    nums[3] = 16;  
    nums[4] = 16; 
    display_commands = nums; 
    new_data = true; 
}

void DISPLAY_scan()
{
    nums[0] = 5; 
    nums[1] = 12;
    nums[2] = 16; 
    nums[3] = 10;  
    nums[4] = 18; 
    display_commands = nums; 
    new_data = true;  
    
}

void DISPLAY_weight(int weight)
{
    int val = weight / 1000; 
    if (val == 0)
        nums[0] = 16;
    else
        nums[0] = weight / 1000;
    
    weight = weight % 1000;
    val = weight / 100; 
    if (val == 0)
        nums[1] = 16;
    else
        nums[1] = val;
    
    nums[2] = 16;
    
    weight = weight % 100; 
    val = weight / 10;
    if (val == 0)
        nums[3] = 16;
    else
        nums[3] = val; 
    
    weight = weight % 10; 
    nums[4] = weight; 
    
    display_commands = nums; 
    new_data = true; 
}

void DISPLAY_time(int mstime)
{
    nums[0] = mstime / 1000;
    mstime = mstime % 1000; 
    nums[1] = mstime / 100;
    nums[2] = 17;
    mstime = mstime % 100; 
    nums[3] = mstime / 10; 
    mstime = mstime % 10; 
    nums[4] = mstime; 
    
    display_commands = nums; 

    new_data = true; 
}

void DISPLAY_CONFIG_Tasks()
{  
    if (I2C1STATbits.TBF)
        return;
    
    switch (_config_state)
    {
        case INIT:
        {
            i = 0;
            // config
            //I2C1BRG = 75; // for 8[MHz]
            I2C1BRG = 500; // for 60[MHz]
         
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
                    _config_state = SEND_BYTE;
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
            }   
            break; 
        }
        case IDLE:
        {
            if(!zero_set)
            {
                zero_set = true; 
            }
        }
    }
}


void DISPLAY_Tasks()
{
    switch(_display_state)
    {
        case WAIT:
        {
            if (new_data)
            {
                i = 0; 
                is_displaying = true; 
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
                    //__delay_ms(5);
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
                    I2C1TRN = numberTable[display_commands[i]];
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
                    is_displaying = false; 
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

bool DISPLAY_is_displaying()
{
    return is_displaying;
}

void DISPLAY_error()
{
    _display_state = SEND_STOP_D;
}
