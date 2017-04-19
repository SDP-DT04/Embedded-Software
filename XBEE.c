/*
 * File:   XBEE.c
 * Author: DT04
 *
 * Created on February 20, 2017, 3:27 PM
 */

#include "xc.h"
#include <libpic30.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include "XBEE.h"
#define FCY 60000000ULL

#define MIN_PACKET_LEN 14

/*
 * Define XBee packets
 */
const uint8_t XBEE_ADDR_PACKET[MIN_PACKET_LEN] = {0x10,0x01,0x00,0x13,0xA2,0x00,0x40,0x60,0xF4,0x98,0xFF,0xFE,0x00,0x00};
xbee_data_t this; 
Xbee_State xbee_state = XBEE_RESET;

void XBEE_transmit(uint8_t* data, uint8_t data_len, uint8_t id)
{
    strncpy((char*)this.data, (char*)data, data_len);
    this.data_len = data_len + 1; 
    this.id = id; 
    this.packet_len = this.data_len + MIN_PACKET_LEN; 
    this.start = true; 
}

void debug(float x)
{
    uint8_t buf[10];
    memset(buf, 0x00, 10);
    sprintf(buf, "%f", x);
    uint8_t i = 0; 
    for (; i < 10; ++i)
    {
        while(!U2STAbits.TRMT); //wait until transmit buffer empty
        U2TXREG = buf[i];
    }
    while(!U2STAbits.TRMT); //wait until transmit buffer empty
        U2TXREG = '\n';
}

void xbee_send(uint8_t x)
{
    while(!U2STAbits.TRMT); //wait until transmit buffer empty
    U2TXREG = x; //load buffer with data
}

Xbee_State xbeeStateReset( void )
{
    this.index = 0; 
    this.start = false; 
    return XBEE_IDLE;
}

Xbee_State xbeeStateIdle( void )
{
    if (this.start)
    {
        this.start = false; 
        return XBEE_START; 
    }
    return XBEE_IDLE; 
}

Xbee_State xbeeStateStart( void )
{
    xbee_send(0x7E);
    return XBEE_LENGTH; 
}

Xbee_State xbeeStateLength( void )
{
    xbee_send( (uint8_t)(this.packet_len>>8) );
    xbee_send( (uint8_t)(this.packet_len) );
    this.index = 0; 
    this.checksum = 0; 
    return XBEE_ADDR; 
}

Xbee_State xbeeStateAddr( void )
{
    if (this.index < MIN_PACKET_LEN)
    {
        xbee_send( XBEE_ADDR_PACKET[this.index] );
        this.checksum += XBEE_ADDR_PACKET[this.index];
        this.index++; 
        return XBEE_ADDR; 
    }
    else
    {
        // send the packet identifier
        xbee_send(this.id);
        this.checksum += this.id;
        
        this.index = 0;
        return XBEE_DATA;
    }
}

Xbee_State xbeeStateData( void )
{
    if (this.index < this.data_len - 1) //-1 since id was already sent!
    {
        xbee_send(this.data[this.index]);
        this.checksum += this.data[this.index];
        this.index++;
        return XBEE_DATA;
    }
    else
    {
        this.index = 0; 
        return XBEE_CHECKSUM; 
    }
}

Xbee_State xbeeStateChecksum( void )
{
    xbee_send(0xFF - this.checksum);
    this.index = 0; 
    this.checksum = 0; 
    return XBEE_IDLE; 
}

void XBEE_Tasks( void )
{
    switch ( xbee_state )
    {
        case XBEE_RESET:
            xbee_state = xbeeStateReset(); 
            break;
            
        case XBEE_IDLE: 
            xbee_state = xbeeStateIdle(); 
            break; 
            
        case XBEE_START:
            xbee_state = xbeeStateStart(); 
            break;
            
        case XBEE_LENGTH:
            xbee_state = xbeeStateLength(); 
            break;
            
        case XBEE_ADDR:
            xbee_state = xbeeStateAddr(); 
            break;
            
        case XBEE_DATA:
            xbee_state = xbeeStateData(); 
            break; 
            
        case XBEE_CHECKSUM:
            xbee_state = xbeeStateChecksum(); 
            break;
    };
}