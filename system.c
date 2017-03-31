#include <stdbool.h>

#include "display.h"
#include "load.h"
#include "mc3635.h"
#include "XBEE.h"
#include "system.h"
#include "rfid.h"

#define MIN_STABLE_TIME 500 // 5 seconds
#define CUSHION 5

static uint32_t timer = 0;
uint32_t last_weight = 0; 

System_State sys_state = RESET; 

bool isSwimming( void )
{
    return (PORTCbits.RC13 == 1);
}

bool isWeightStable(uint32_t weight)
{
    uint32_t diff = 0; 
            
    DISPLAY_weight( weight );
    if ( last_weight > weight )
        diff = last_weight - weight; 
    else
        diff = weight - last_weight; 
            
    if (diff <= CUSHION )
        timer++; 
    else
        timer = 0;
    
    last_weight = weight; 
    
    return ( timer > MIN_STABLE_TIME );
}

System_State systemStateReset( void )
{
    DISPLAY_weight(0);
    timer = 0; 
    
    return WEIGH; 
}

System_State systemStateWeigh( void )
{
     DISPLAY_weight( LOAD_get() );
     if ( isWeightStable( LOAD_get() ) )
     {
         timer = 0; 

         return BLINK;
     }
     return WEIGH;
}

System_State systemStateBlink( void )
{
    if ( (timer / 100) % 2 )
         DISPLAY_weight( 0 );
     else
         DISPLAY_weight( last_weight );

     if (timer > 1000)
     {
         DISPLAY_time(0);
         return WAIT; 
     }
     timer++;
     return BLINK;
}

System_State systemStateWait( void )
{
    if ( isSwimming() )
    {
        uint8_t tag[RFID_TAG_LEN];
        RFID_get( tag );
        XBEE_transmit(tag, RFID_TAG_LEN);
        timer = 0; 
        return SWIM; 
    }
    return WAIT; 
}

System_State systemStateSwim( void )
{
    timer++; 
    DISPLAY_time(timer);
 
    uint8_t accel[2];
    accel[0] = mc3635_read_z_low(); 
    accel[1] = mc3635_read_z_high(); 
    
    XBEE_transmit(accel, 2);
    
    if ( !isSwimming() )
    {
        timer = 0; 
        return WAIT; 
    }
    return SWIM; 
}

void system_tasks( void )
{
    switch ( sys_state )
    {
        case RESET: 
            sys_state = systemStateReset(); 
            break; 
       
        case WEIGH:
            sys_state = systemStateWeigh(); 
            break;
            
        case BLINK:
            sys_state = systemStateBlink(); 
            break;
           
        case WAIT:
            sys_state = systemStateWait(); 
            break;
            
        case SWIM: 
            sys_state = systemStateSwim(); 
            break; 
    };
}