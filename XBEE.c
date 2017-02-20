/*
 * File:   XBEE.c
 * Author: DT04
 *
 * Created on February 20, 2017, 3:27 PM
 */


#include "xc.h"
#include "XBEE.h"
#include "stdbool.h"

unsigned char initialize_XBEE[19] = {0x7E,0x00,0x0F,0x10,0x01,0x00,0x13,0xA2,0x00,0x40,0x60,0xF4,0x98,0xFF,0xFE,0x00,0x00,0x00,0x10};
unsigned char RFID_XBEE[34]; //{0x7E,0x00,0x1F,0x10,0x01,0x00,0x13,0xA2,0x00,0x40,0x60,0xF4,0x98,0xFF,0xFE,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00};
unsigned char weight_XBEE[20]; // = {0x7E,0x00,0x10,0x10,0x01,0x00,0x13,0xA2,0x00,0x40,0x60,0xF4,0x98,0xFF,0xFE,0x00,0x00,0xFF,0xFF,0x00};
unsigned char accel_XBEE[118];
unsigned char done_XBEE[19] = {0x7E,0x00,0x0F,0x10,0x01,0x00,0x13,0xA2,0x00,0x40,0x60,0xF4,0x98,0xFF,0xFE,0x00,0x00,0x03,0x0D};

enum XBEE_state{
    WAIT,
    INIT,
    RFID,
    WEIGHT,
    ACCEL,
    DONE,
};

enum XBEE_state _xbee_state = WAIT; 

bool xbee_new_data = true;
static int i = 0;

void xbee_tasks()
{
    switch (_xbee_state)
    {
        case WAIT:
        {
            if (xbee_new_data)
            {
                xbee_new_data = false; 
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
                _xbee_state = RFID; 
                i = 0;
            }
        }
    }
    
}