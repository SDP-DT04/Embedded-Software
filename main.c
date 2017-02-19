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
#define FCY 60000000ULL
//#define FCY 8000000ULL
#include <libpic30.h>

char ReceivedChar[16] = {"0000000000000000"};
int p = 0, j = 0, k = 0, m = 0, n = 0, c=0, success=0;
unsigned char byteRead;
const int tagLen = 16;
const int idLen = 13; //idLen = 13  because 12 data plus NULL
const int kTags = 4; //total number of tags
char nTag[12];
char oTag[12];
char knownTags[12] = {"82003BE82372"};
char newTag[16]={"0000000000000000"}; //idLen = 13  because 12 data plus NULL
char tagData[12]={"000000000000"};
char test[12] = {"82003BE82372"};

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
    1,
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
bool Start = false;

enum I2C_Display_State _display_state = WAIT; 
enum I2C_Config_State _config_state = INIT; 
bool new_data = false;
bool displaying = false; 
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
           // display_time(5690);
        }
    }
}

void display_time(int mstime)
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
//    int j=0;
//    for(j=0;j<5;j++)
//    {
//        
//        display_commands[j]=nums[j];
//    }
//    _display_state = WAIT; 
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
                displaying = true; 
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
                    displaying = false; 
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

int error_counter = 0; 
int dSec = 0;
void _ISR __attribute__((auto_psv))  _T1Interrupt(void)
{
    if (Start == false)
    {
        if (PORTCbits.RC13 == 1)
        {
            Start = true;
            TMR1=0;
            dSec=0;
        }
        
        else if (PORTCbits.RC13 == 0)
        {}
    }
    
    else if(Start == true)
    {
        if (PORTCbits.RC13 == 1)
        {
            if (dSec<9999)
            {dSec++;}
            else 
            {dSec = 0;}
            
            if (!displaying)
            {
                display_time(dSec);
                error_counter = 0; 
            }
            else
            {error_counter++;}
                
            if (error_counter > 5)
            {_display_state = SEND_STOP_D;}
        }
        
        else if (PORTCbits.RC13 == 0)
        {
        Start = false;
        TMR1=0;
        }
    }
 _T1IF = 0;//clear  the  flag
}

int main(void)
{
    ConfigureClock(); //Configure Clock to 60[MHz]
    TRISAbits.TRISA0 = 0; //Set pin 13 (RA0) as output
    TRISDbits.TRISD8 = 0; //Set pin 42 (RD8) as output
    ANSELAbits.ANSA12=0; //Set pin 11 (RA12) as digital pin
    TRISCbits.TRISC13 = 0b1; //Set pin 47 (RC13) as input
    U1MODEbits.STSEL = 0; //1-stop bit
    U1MODEbits.PDSEL = 0; //No parity, 8-bit data
    U1MODEbits.ABAUD = 0; //Auto baud rate is disabled
    U1MODEbits.BRGH = 0; //Standard baud rate
    U1BRG = 390; //Set baud rate register
    U1MODEbits.UARTEN = 1; //Enable UART
    IEC0bits.U1RXIE = 1; //Enable RX UART interrupt 
    U1STAbits.UTXEN = 1;//Set TX to Enable
    U1STAbits.URXISEL = 0b00; //Load 1 bytes in U1RXREG
    
    RPINR18bits.U1RXR = 0b0100111; //Set pin 46 (RP39) to U1RX pin
    RPOR5bits.RP54R = 0b000001; //Set pin 50 (RP54) as U1TX pin
    PORTDbits.RD8 = 1; //Set pin 42 (RD8) high for LED
    __delay_ms(1000);
    new_data = false; 
    
    _T1IP = 4; //Interrupt setup
    TMR1 = 0; //Set timer 1 to zero
    T1CON = 0x8030; //Enable timer 1 and ser prescalar to 256 
    PR1 = 2360;//creates 10[ms] timer for 60[MHz]
    //PR1= 313; //creates 10[ms] timer for 8[MHz]
    _T1IF = 0;
    _T1IE = 1;
    
    while(1)
    {
        config_tasks();
        display_tasks();
    }
    return 0;
}

void __attribute__((__interrupt__)) _U1RXInterrupt(void)
{
    static int i=0;
    while(U1STAbits.URXDA)
    {
        byteRead=U1RXREG;       //Read in data from register
        while(!U1STAbits.TRMT); //Wait until able to transmit 
        U1TXREG=byteRead;       //Transmit
        while(!U1STAbits.TRMT); //Wait until able to transmit 
        newTag[i]=byteRead;
        i++;
    }
    IFS0bits.U1RXIF = 0;    //Clear Flag
}
