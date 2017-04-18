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
#define R_STOP_VALUE 1.25
#define R_START_VALUE 3.5
#define ACCEL_LEN 50

static uint32_t timer = 0;
static uint32_t swim_time = 0;  
static uint32_t start_time = 0;  
static uint32_t stop_time = 0;  
uint32_t last_weight = 0; 
uint8_t a_index = 0; 
uint8_t accel[ACCEL_LEN];

System_State sys_state = RESET; 

bool bucket_tilted( void )
{
    /* read the x axis */
    accel[0] = mc3635_read_x_low(); 
    accel[1] = mc3635_read_x_high(); 
    short value = (accel[1] << 8) | accel[0];
    
    if (value > 2000 || value < -2000 )
        return true; 
    
    /* read the y axis */
    accel[0] = mc3635_read_y_low(); 
    accel[1] = mc3635_read_y_high(); 
    value = (accel[1] << 8) | accel[0];
    
    if (value > 2000 || value < -2000 )
        return true; 
    
    return false; 
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
         swim_time = 0;
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
    float R = ALG_Calculate_R(value);
  
    /* wait for at least 3 seconds or the amount of time it took to swim */
    if (timer > swim_time && timer > 300) 
    {
        /* R value must be consistent for 300ms */
        if ( R > R_START_VALUE)
        {
            if (start_time == 0)
            {
                start_time = timer; 
            }
            else
            {
                if (bucket_tilted())
                {
                    start_time = 0; 
                }
                else if (start_time - timer > 30)
                {
                    uint8_t tag[RFID_TAG_LEN];
                    RFID_get( tag );
                    XBEE_transmit(tag, RFID_TAG_LEN, 0x01);
                    stop_time = 0; 
                    a_index = 0; 
                    timer = 30; 
                    return SWIM;    
                }
            }
        }
        else
        {
            start_time = 0;
        }
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
    
    /* wait at least 3s, since no swim will be quicker*/
    if (timer > 300)
    {
        /* special case: the swimmer never actually started */
        if (R < R_STOP_VALUE && timer == 301)
        {
            DISPLAY_time(0);
            a_index = 0; 
            swim_time = 0; 
            timer = 0; 
            start_time = 0; 
            ALG_Init_R();
            return WAIT;             
        }
        else if (R < R_STOP_VALUE)
        {
            if (stop_time == 0)
            {
                stop_time = timer; 
            }
            else
            {
                if (stop_time - timer > 30)
                {
                    DISPLAY_time(timer - 30);
                    XBEE_transmit(accel, a_index, 0x03); // transmit the remaining acceleration data
                    a_index = 0;
                    swim_time = timer; 
                    timer = 0;
                    return END;
                }
            }
        }
        else
        {
            stop_time = 0; 
        }   
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
    
    start_time = 0; 
    ALG_Init_R();
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