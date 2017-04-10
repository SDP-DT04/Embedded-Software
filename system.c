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
#define R_STOP_VALUE 3
#define R_START_VALUE 25
#define ACCEL_LEN 50

static uint32_t timer = 0;
static uint32_t swim_time = 0; 
uint32_t last_weight = 0; 
uint8_t a_index = 0; 
uint8_t accel[ACCEL_LEN];

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
    
        return WEIGH;   
    }
    return RESET; 
}

System_State systemStateWeigh( void )
{
     DISPLAY_weight( LOAD_get() );
     if (  timer > 100)//isWeightStable( LOAD_get() ) )
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
         uint8_t temp = 0; 
         XBEE_transmit(&temp, 1, 0x00); //let the server know to initialize
         timer = 0; 
         DISPLAY_time(0);
         ALG_Init_R();
         return WAIT; 
     }
     timer++;
     return BLINK;
}

System_State systemStateWait( void )
{
    timer++; 
    accel[0] = mc3635_read_z_low(); 
    accel[1] = mc3635_read_z_high(); 
    
    short value = (accel[1] << 8) | accel[0];
    //debug(value);
    float R = ALG_Calculate_R(value);
  
    //if (timer < 500)
      //  return;     //give some time for the algorithm to adjust
    
    if ( R > R_START_VALUE )//&& timer > swim_time)
    {
        uint8_t tag[RFID_TAG_LEN];
        RFID_get( tag );
        XBEE_transmit(tag, RFID_TAG_LEN, 0x01);
        a_index = 0; 
        timer = 0; 
        return SWIM; 
    }
    return WAIT; 
}

System_State systemStateSwim( void )
{
    timer++; 
    DISPLAY_time(timer);
 
    accel[a_index++] = mc3635_read_z_low(); 
    accel[a_index++] = mc3635_read_z_high(); 
    
        
    short value = (accel[a_index-1] << 8) | accel[a_index-2];
   
    if (a_index == ACCEL_LEN)
    {
        XBEE_transmit(accel, ACCEL_LEN, 0x03);
        a_index = 0; 
    }
    
    float R = ALG_Calculate_R(value);
    //debug(value);
    
    //if (timer > 1002)
    if ( R < R_STOP_VALUE )
    {
        XBEE_transmit(accel, a_index, 0x03);
        a_index = 0;
        swim_time = timer; 
        timer = 0;
        return END;
    }
    return SWIM; 
}

System_State systemStateEnd( void )
{
    uint8_t temp = 0; 
    XBEE_transmit(&temp, 1, 0x03); //let the server know the workout is over
    return RETURN; 
}

System_State systemStateReturn( void )
{
    uint8_t temp = 0; 
    XBEE_transmit(&temp, 1, 0x00); //let the server know to initialize
    return WAIT;
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
            
        case END:
            sys_state = systemStateEnd(); 
            break;
            
        case RETURN:
            sys_state = systemStateReturn(); 
            break;
            
        case ERROR:
            break;
    };
}