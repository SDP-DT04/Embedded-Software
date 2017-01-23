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
int  dSec = 0, Sec = 0; // two  global  variables

//add in interupt

int main(void)
{
    ConfigureClock();
    I2Cinit(299);
    ConfigureModuleADC();
    //ChangeChannelADC(1);
    /*_T1IP = 4;//interupt setup
    TMR1 = 0;
    T1CON = 0x8010;
    PR1 = 16000-1;
    _T1IF = 0;
    _T1IE = 1;*/
      
    double ADC_value1 = 0;
    double ADC_value2 = 0;
    double Voltage1 = 0;
    double Voltage2 = 0;
    int v1 = 0;
    int v2 = 0;
    //int weight = 0;
    //float constant = 40;//constant with voltage to weight relationship

    ANSELAbits.ANSA1 = 1;
    ANSELAbits.ANSA11 = 1;
    TRISAbits.TRISA0 = 0;
    
    char c1[4]= {"0000"};
    char c2[4]= {"0000"};
    
    while(1)
    {
        PORTAbits.RA0 = 1;      
        ADC_value1 = getADC();
        Voltage1 = (ADC_value1*3250)/(4096);//3250 is 1000 times its value for an easier displayed value
        //v1 = Voltage1;
        sprintf(c1, "%04f", Voltage1);//change weight int into char array
        display(c1, 1);
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



    
   
    
 