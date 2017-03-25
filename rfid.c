#include <stdint.h>
#include <string.h>

#include "rfid.h"

#define START_BYTE 0x02
#define CR 0x0D
#define LF 0x0A
#define END_BYTE 0x03

static uint8_t tag[RFID_TAG_LEN];
static uint8_t tag_index = 0; 

void RFID_get( uint8_t* ntag )
{
    strncpy((char*)ntag, (char*)tag, RFID_TAG_LEN); 
}

void RFID_new_byte( uint8_t x )
{
    switch( x )
    {
        case START_BYTE:
            tag_index = 0;
            break;
      
        case CR: 
        case LF:
        case END_BYTE:
            break;
            
        default:
            tag[tag_index++] = x; 
    };
}