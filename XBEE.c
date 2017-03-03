/*
 * File:   XBEE.c
 * Author: DT04
 *
 * Created on February 20, 2017, 3:27 PM
 */


#include "xc.h"
#include "XBEE.h"
#include "stdbool.h"
#include "accelData.h"
#define FCY 60000000ULL
//#define FCY 8000000ULL
#include <libpic30.h>

/*
 * Define XBee packets
 */
unsigned char initialize_XBEE[19] = {0x7E,0x00,0x0F,0x10,0x01,0x00,0x13,0xA2,0x00,0x40,0x60,0xF4,0x98,0xFF,0xFE,0x00,0x00,0x00,0x10};
unsigned char RFID_XBEE[17] = {0x7E,0x00,0x1F,0x10,0x01,0x00,0x13,0xA2,0x00,0x40,0x60,0xF4,0x98,0xFF,0xFE,0x00,0x00};
unsigned char WEIGHT_XBEE[17]  = {0x7E,0x00,0x10,0x10,0x01,0x00,0x13,0xA2,0x00,0x40,0x60,0xF4,0x98,0xFF,0xFE,0x00,0x00};//0xFF,0xFF,0x00};
unsigned char ACCEL_XBEE[17]  = {0x7E,0x00,0x73,0x10,0x01,0x00,0x13,0xA2,0x00,0x40,0x60,0xF4,0x98,0xFF,0xFE,0x00,0x00};
unsigned char DONE_XBEE[19] = {0x7E,0x00,0x0F,0x10,0x01,0x00,0x13,0xA2,0x00,0x40,0x60,0xF4,0x98,0xFF,0xFE,0x00,0x00,0x03,0x0D};

/*
 * Define RFID, weight, and acceleration buffers
 */
unsigned char newTag[16] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00};
unsigned char newWeight[1] = {0x38};
uint8_t mc3635_data[100];

bool mc3635_new_data = false; 
uint8_t mc3635_w_index = 0; 
uint8_t mc3635_r_index = 0; 
bool xbee_is_transmitting = false;

enum XBEE_state{
    WAIT,
    INIT,
    RFID,
    WEIGHT,
    ACCEL,
    DONE,
};
enum XBEE_state _xbee_state = WAIT; 



static int i = 0, j = 0;;
unsigned char checksum; 

void xbee_tasks()
{
    switch (_xbee_state)
    {
        case WAIT:
        {
            if (xbee_is_transmitting)
            {
                i = 0;
                checksum = 0; 
                xbee_is_transmitting = false; 
                _xbee_state = INIT; 
            }
            break; 
        }
        
        case INIT:
        {
            while(!U2STAbits.TRMT);
            U2TXREG = initialize_XBEE[i];
            i++;
            if(i == 19)
            {
                checksum = 0; 
                _xbee_state = RFID; 
                i = 0;
               // __delay_ms(100);
            }
            break;
        }
        
        case RFID:
        {
            while(!U2STAbits.TRMT);
            if (i<17)
            {
                if (i > 2)
                {
                    checksum += RFID_XBEE[i];
                }
                U2TXREG = RFID_XBEE[i];
            }
            else if (i == 17)
            {
                checksum += 0x01;
                U2TXREG = 0x01; 
            }
            else if (i > 17 && i < 34) 
            {
                checksum += newTag[i-18];
                U2TXREG = newTag[i-18];
            }
            else
            {
                U2TXREG = 0xFF - checksum; 
                _xbee_state = WEIGHT;
                checksum = 0;
                i=0; 
                break;
            }
            i++;
            break;
        }
        case WEIGHT:
        {
            while(!U2STAbits.TRMT); //wait for transmit buffer to be empty before sending 
            if (i<17)
            {
                if (i > 2)
                {
                    checksum += WEIGHT_XBEE[i];
                }
                U2TXREG = WEIGHT_XBEE[i];
            }
            else if (i == 17)
            {
                checksum += 0x02;
                U2TXREG = 0x02; 
            }
            else if (i == 18) 
            {
                checksum += newWeight[i-18];
                U2TXREG = newWeight[i-18];
            }
            else
            {
                U2TXREG = 0xFF - checksum; 
                _xbee_state = ACCEL;
                checksum = 0;
                i=0; 
                break; 
            }
            i++;
            break;
        }
        case ACCEL:
        {
            while(!U2STAbits.TRMT); //wait for transmit buffer to be empty before sending 
            if (i<17)
            {
                if (i > 2)
                {
                    checksum += ACCEL_XBEE[i];
                }
                U2TXREG = ACCEL_XBEE[i];
            }
            else if (i == 17)
            {
                checksum += 0x03;
                U2TXREG = 0x03; 
            }
            else if (i > 17 && i < 118) 
            {
                if (mc3635_r_index < mc3635_w_index || mc3635_r_index > mc3635_w_index)
                {
                    checksum += mc3635_data[mc3635_r_index];
                    U2TXREG = mc3635_data[mc3635_r_index++];
                    
                    if (mc3635_r_index == MC3635_BUF_LEN)//wrap index?
                        mc3635_r_index = 0;
                }
                else if (!xbee_is_transmitting)
                {
                    //done with sending data; fill up the rest of the packet
                    U2TXREG = 0x00;
                }
                else
                {
                    //no new data; repeat this step
                    --i; 
                }
            }
            else
            {
                U2TXREG = 0xFF - checksum; 
                if(xbee_is_transmitting){
                    _xbee_state = ACCEL;
                    checksum = 0;
                    i = 0;
                    break;
                }else{
                    _xbee_state = DONE;
                    checksum = 0;
                    i=0; 
                    j=0;
                    break; 
                }
            }
            i++;
            break;
        }
        
        case DONE:
        {
            while(!U2STAbits.TRMT);
            U2TXREG = DONE_XBEE[i];
            i++;
            if(i == 19)
            {
                checksum = 0; 
                _xbee_state = WAIT; 
                i = 0;
               // __delay_ms(100);
            }
            break;
        }
    }
    
}