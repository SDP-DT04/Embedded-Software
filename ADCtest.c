/*
 * File:   ADCtest.c
 * Author: DT04
 *
 * Created on January 10, 2017, 4:19 PM
 */

#include "config.h"
#include "functions.h"
#include <xc.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define FCY 60000000ULL
#include <libpic30.h>
#include <math.h>

int main(void)
{
    float ADC_value1 = 0;
    float ADC_value2 = 0;
    float V1 = 0;
    float V2 = 0;
    char c1[4]= {"0000"};
    char c2[4]= {"0000"};
    int dif = 0;
    ANSELAbits.ANSA1 = 1; //Configures AN1 as an analog input
    ANSELAbits.ANSA11 = 1; //Configures AN9 as an analog input
    
    ConfigureClock();
    I2Cinit(299);
    ConfigureModuleADC();
    
    
    while(1)
    {
        while(!_AD1IF);
        _AD1IF = 0;
        
        ADC_value1 = ADC1BUF0;
        ADC_value2 = ADC1BUF1;
        V1 = (ADC_value1*3.25)/4096;
        V2 = (ADC_value2*3.25)/4096;
        dif = abs((V1-V2)*100000);
        sprintf(c1, "%04d", dif);//change weight int into char array
        display(c1, 1);
        __delay_ms(1000);
    }
    return 0;
}