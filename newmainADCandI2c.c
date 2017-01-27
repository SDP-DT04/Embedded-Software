/*
 * File:   newmainADCandI2c.c
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
#define ADC 4096
#define Volt 3.25
int  dSec = 0, Sec = 0; // two  global  variables


int main(void)
{
    ConfigureClock();
    I2Cinit(299);
    ConfigureModuleADC();
              
    double ADC_value[10] = {0};
    double samp[10] = {0};
    double Voltage[10] = {0};
    double Voltage1 = 0, Voltage2 = 0;
    double ZeroV_value = 0;
    double low_lim = 0 , upp_lim = 0;
    char c1[4]= {"0000"};
    char c2[4]= {"0000"};
    int i = 0, j = 0, a = 0, b = 0;
    
    ANSELAbits.ANSA11 = 1;
    
//    Calibrate zero position on scale
    __delay_ms(2000);
    for (a=0; a<10; a++)
        {
            for (b = 0; b<10; b++)
            {
                ADC_value[b] = getADC();
                samp[b] = (ADC_value[b] * Volt) / (ADC);
                __delay_us(10);
            }
            Voltage[a] = ((samp[0] + samp[1] + samp[2] + samp[3] + samp[4] + samp[5] + samp[6] + samp[7] + samp[8] + samp[9]) / 10);
        }
    ZeroV_value = ((Voltage[0]+Voltage[1]+Voltage[2]+Voltage[3]+Voltage[4]+Voltage[5]+Voltage[6]+Voltage[7]+Voltage[8]+Voltage[9])/10);
    low_lim = ZeroV_value-0.025;
    upp_lim = ZeroV_value+1;
        
    while(1)
    {
        PORTAbits.RA0 = 1;
        for (i= 0; i<10; i++)
        {
            for (j = 0; j<10; j++)
            {
                ADC_value[j] = getADC();
                samp[j] = (ADC_value[j] * Volt) / (ADC);
                __delay_us(10);
            }
            Voltage[i] = ((samp[0] + samp[1] + samp[2] + samp[3] + samp[4] + samp[5] + samp[6] + samp[7] + samp[8] + samp[9]) / 10);
        }
        Voltage1 = ((Voltage[0]+Voltage[1]+Voltage[2]+Voltage[3]+Voltage[4]+Voltage[5]+Voltage[6]+Voltage[7]+Voltage[8]+Voltage[9])/10);
        //Voltage1 = Voltage2*1000;
                
        if ((Voltage1>(low_lim)) && (Voltage1<(upp_lim)))
        {
            char temp[4]={"0000"};
            strncpy(c1,temp,4);
            display(c1, 1);
        }
        
        else if ((Voltage1>(low_lim - 0.1)) && (Voltage1<(low_lim - 0.000000000001)))
        {   
            char temp[4]={"0005"};
            strncpy(c1,temp,4);
            display(c1, 1);
        }
            
        else if ((Voltage1>(low_lim - 0.2)) && (Voltage1<(low_lim - 0.100000000001)))
        {
            char temp[4]={"0010"};
            strncpy(c1,temp,4);
            display(c1, 1);
        }
        
        else if ((Voltage1>(low_lim - 0.3)) && (Voltage1<(low_lim - 0.200000000001)))
        {
            char temp[4]={"0015"};
            strncpy(c1,temp,4);
            display(c1, 1);
        }
        
        else if ((Voltage1>(low_lim - 0.4)) && (Voltage1<(low_lim - 0.30000000001)))
        {
            char temp[4]={"0020"};
            strncpy(c1,temp,4);
            display(c1, 1);
        }
        
        else if (Voltage1>(upp_lim))
        {
            char temp[4]={"9999"}; //Voltage1 too high
            strncpy(c1,temp,4);
            display(c1, 1);   
        }
        
        else    //(Voltage1<(low_lim-.321)
        {
            char temp[4]={"1111"}; //Voltage1 too low
            strncpy(c1,temp,4);
            display(c1, 1);   
        }

//        sprintf(c1, "%04f", Voltage1);//change weight int into char array
//        display(c1, 1);
        __delay_ms(500);
//        PORTAbits.RA0 = 0;
//        ChangeChannelADC(10);
//        ADC_value2 = getADC9();
//        Voltage2 = (ADC_value2*3250)/(4096);//3250 is 1000 times its value for an easier displayed value
//        //v2 = Voltage2;
//        sprintf(c2, "%04f", Voltage2);//change weight int into char array
//        display(c2, 1);
//        __delay_ms(3000);
    }
    return 0;
}
                 
//void sprintf(char Voltagestring, "%f [V]", int Voltage){
//
//        PMADDR = 0x0000; // write command , not data
//        PMDIN1 = 0xc0; // 0x0c | 0x40
//        WriteString2LCD(Voltagestring);
//        while(is_LCD_Busy()); // keep waiting if the LCD is busy
//        while(PMMODEbits.BUSY); // wait for PMP to be available
//        msdelay(50);
//}