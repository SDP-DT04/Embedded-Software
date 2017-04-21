#include <stdbool.h>

#include "display.h"
#include "load.h"
#include "mc3635.h"
#include "XBEE.h"
#include "system.h"
#include "rfid.h"
#include "algorithm.h"

#define MIN_STABLE_TIME 1000 // 10 seconds
#define CUSHION 2
#define R_STOP_VALUE 1.25
#define R_START_VALUE 3.25
#define ACCEL_LEN 50

static uint32_t timer = 0;
static uint32_t timer2 = 0;
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
    
    if (value > 500 || value < -500 )
        return true; 
    
    /* read the y axis */
//    accel[0] = mc3635_read_y_low(); 
//    accel[1] = mc3635_read_y_high(); 
//    value = (accel[1] << 8) | accel[0];
//    
//    if (value > 1000 || value < -1000 )
//        return true; 
    
    return false; 
}

bool isWeightStable(uint32_t weight)
{
    uint32_t diff = 0; 
            
    if ( last_weight > weight )
        diff = last_weight - weight; 
    else
        diff = weight - last_weight; 
            
    if (diff <= CUSHION )
        timer2++; 
    else
        timer2 = 0;
    
    last_weight = weight; 
    
    return ( timer2 > MIN_STABLE_TIME );
}

System_State systemStateReset( void )
{   
    if (DISPLAY_config_done())
    {
        DISPLAY_scan();
        timer = 0; 
    
       return SCAN;   
    }
    return RESET; 
}

System_State systemStateScan( void )
{   
    if (RFID_new_scan())
    {
       return WEIGH;   
    }
    return SCAN; 
}

System_State systemStateWeigh( void )
{
    timer++; 
    if (timer % 100 == 0)
        DISPLAY_weight( LOAD_get() ); // display weight every 1s
        //debug_u(LOAD_get());
        
    //return WEIGH;
    if (LOAD_get() < 5) //wait until weight is applied
        return WEIGH; 
    
    //if (false)
    if ( isWeightStable( LOAD_get() ))
     {
        uint8_t w[1];
        w[0] = 50; 
         timer = 0; 
         timer2 = 0; 
         XBEE_transmit(w, 1, 0x02);
         return BLINK;
     }
     
     return WEIGH;
}

System_State systemStateBlink( void )
{
    if ( (timer / 100) % 2 )
         DISPLAY_blank();
     else
         DISPLAY_weight( last_weight );

     if (timer > 600)
     {
         uint8_t temp = 0; 
         //XBEE_transmit(&temp, 1, 0x00); //let the server know to initialize
         timer = 0; 
         swim_time = 0;
         start_time = 0; 
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
    //debug(R);
    if (timer > swim_time)
        DISPLAY_time(0);
    
    /* wait for at least 3 seconds or the amount of time it took to swim */
   
    if (timer > swim_time && timer > 300) 
    {
        if (LOAD_get() > last_weight + CUSHION + 5)
        {
            timer = 0; 
            return WEIGH;
        }
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
                    timer = 0; 
                    return WEIGH; 
                }
                else if (start_time - timer > 50)
                {
                    uint8_t tag[RFID_TAG_LEN];
                    RFID_get( tag );
                    XBEE_transmit(tag, RFID_TAG_LEN, 0x01);
                    stop_time = 0; 
                    a_index = 0; 
                    timer = 50; 
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
        if (R < R_STOP_VALUE && timer < 400)
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
                if (stop_time - timer > 35)
                {
                    DISPLAY_time(timer - 35);
                    XBEE_transmit(accel, a_index, 0x03); // transmit the remaining acceleration data
                    a_index = 0;
                    swim_time = timer + 500; 
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
    uint16_t x = swim_time - 500 - 35;
    uint8_t temp[2];
    temp[0] = (uint8_t)x; 
    temp[1] = (uint8_t)(x >> 8);
    XBEE_transmit(temp, 2, 0x04); //transmit the swim time
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
       
        case SCAN:
            sys_state = systemStateScan(); 
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
