#include <stdbool.h>

#include "display.h"
#include "load.h"
#include "mc3635.h"
#include "XBEE.h"
#include "system.h"
#include "rfid.h"
#include "algorithm.h"

#define MIN_STABLE_TIME 500 // 5 seconds
#define CUSHION 5
#define R_STOP_VALUE 0.001
#define R_START_VALUE 1


static uint32_t timer = 0;
uint32_t last_weight = 0; 

System_State sys_state = RESET; 

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
    if (DISPLAY_config_done())
    {
        DISPLAY_weight(0);
        timer = 0; 
    
        return BLINK;   
    }
    return RESET; 
}

System_State systemStateWeigh( void )
{
     DISPLAY_weight( LOAD_get() );
     if (  timer > 500)//isWeightStable( LOAD_get() ) )
     {
         timer = 0; 

         return BLINK;
     }
     timer++; 
     return WEIGH;
}

System_State systemStateBlink( void )
{
    if ( (timer / 100) % 2 )
         DISPLAY_blank();
     else
         DISPLAY_weight( 50 );

     if (timer > 100)
     {
         uint8_t temp; 
         XBEE_transmit(&temp, 0, 0x00); //let the server know to initialize
         DISPLAY_time(0);
         ALG_Init_R();
         return WAIT; 
     }
     timer++;
     return BLINK;
}

System_State systemStateWait( void )
{
    uint8_t accel[2];
    accel[0] = mc3635_read_z_low(); 
    accel[1] = mc3635_read_z_high(); 
    
    short value = (accel[1] << 8) | accel[0];
    
    
    debug(ALG_Calculate_R(value));
    if (false)
   // if ( ALG_Calculate_R(value) > R_START_VALUE )
    {
        uint8_t tag[RFID_TAG_LEN];
        RFID_get( tag );
        XBEE_transmit(tag, RFID_TAG_LEN, 0x01);
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
        
    short value = (accel[1] << 8) | accel[0];
    XBEE_transmit(accel, 2, 0x03);
    
    if ( ALG_Calculate_R(value) < R_STOP_VALUE )
    {
       XBEE_transmit(accel, 0, 0x03); //let the server know the workout is over
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