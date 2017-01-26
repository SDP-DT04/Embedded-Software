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
    //ConfigureModuleADC();
    initAdc1();
          
    double ADCv0 = 0, ADCv1 = 0, ADCv2 = 0, ADCv3 = 0, ADCv4 = 0, ADCv5 = 0, ADCv6 = 0, ADCv7 = 0, ADCv8 = 0, ADCv9 = 0;
    double samp0 = 0, samp1 = 0, samp2 = 0, samp3 = 0, samp4 = 0, samp5 = 0, samp6 = 0, samp7 = 0, samp8 = 0, samp9 = 0;
    double Voltage[10] = {0};
    double Voltage1 = 0;
    double Voltage2 = 0;
    int v1 = 0;
    int v2 = 0;
    //int weight = 0;
    //float constant = 40;//constant with voltage to weight relationship

//    ANSELAbits.ANSA1 = 1;
//    ANSELAbits.ANSA11 = 1;
//    TRISAbits.TRISA0 = 0;
    
    char c1[4]= {"0000"};
    char c2[4]= {"0000"};
    int i = 0;
    while(1)
    {
        for (i= 0; i<10; i++)
        {
            PORTAbits.RA0 = 1;
            ADCv0 = getADC();
            samp0 = (ADCv0 * Volt) / (ADC);
            __delay_ms(10);
            ADCv1 = getADC();
            samp1 = (ADCv1 * Volt) / (ADC); //3250 is 1000 times its value for an easier displayed value
            __delay_ms(10);
            ADCv2 = getADC();
            samp2 = (ADCv2 * Volt) / (ADC);
            __delay_ms(10);
            ADCv3 = getADC();
            samp3 = (ADCv3 * Volt) / (ADC);
            __delay_ms(10);
            ADCv4 = getADC();
            samp4 = (ADCv4 * Volt) / (ADC);
            __delay_ms(10);
            ADCv5 = getADC();
            samp5 = (ADCv5 * Volt) / (ADC);
            __delay_ms(10);
            ADCv6 = getADC();
            samp6 = (ADCv6 * Volt) / (ADC);
            __delay_ms(10);
            ADCv7 = getADC();
            samp7 = (ADCv7 * Volt) / (ADC);
            __delay_ms(10);
            ADCv8 = getADC();
            samp8 = (ADCv8 * Volt) / (ADC);
            __delay_ms(10);
            ADCv9 = getADC();
            samp9 = (ADCv9 * Volt) / (ADC);
            __delay_ms(10);
            Voltage[i] = ((samp0 + samp1 + samp2 + samp3 + samp4 + samp5 + samp6 + samp7 + samp8 + samp9) / 10);
        }
        Voltage1 = (Voltage[0]+Voltage[1]+Voltage[2]+Voltage[3]+Voltage[4]+Voltage[5]+Voltage[6]+Voltage[7]+Voltage[8]+Voltage[9])/10;
        
//        sprintf(c1, "%04f", Voltage1);//change weight int into char array
//        display(c1, 1);
        __delay_ms(3000);
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



    
   
    
 