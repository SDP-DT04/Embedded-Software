/*
 * File:   main.c
 * Author: DT04
 *
 * Created on February 6, 2017, 12:50 PM
 */

//CARL
#include "config.h"
#define FCY 60000000ULL

/* C Libs */
#include <libpic30.h>
#include <stdbool.h>
#include "xc.h"

/* User Libs */
#include "display.h"
#include "functions.h"
#include "xc.h"
#include "accelData.h"
#include "XBEE.h"
#include "mc3635.h"
#include "setup.h"

int main(void)
{
    /* Initialization */
    CLOCK_init();
    UART1_init(); 
    UART2_init(); 
    TIMER1_init(); 
    mc3635_init();
    ADC_init(); 
    __delay_ms(1000); //wait for sensors to start up
    
    while(1)
    {
        DISPLAY_CONFIG_Tasks();
        DISPLAY_Tasks();
        XBEE_Tasks();
    }
    return 0;
}