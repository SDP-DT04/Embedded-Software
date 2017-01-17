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

int  dSec = 0, Sec = 0; // two  global  variables

//add in interupt

int main(void)
{
    /*_T1IP = 4;//interupt setup
    TMR1 = 0;
    T1CON = 0x8010;
    PR1 = 16000-1;
    _T1IF = 0;
    _T1IE = 1;*/
      
    float ADC_value = 0;
    float Voltage = 0;
    int v = 0;
    int weight = 0;
    float constant = 40;//constant with voltage to weight relationship

    
    TRISAbits.TRISA0 = 0;
    TRISAbits.TRISA1 = 1;
   
    I2Cinit(37);
    ConfigureModuleADC();
    ChangeChannelADC(1);
    
    char c[4]= {"0000"} ;
    
    while(1)
    {
        PORTAbits.RA0 = 1;
               
        ADC_value = getADC();
        Voltage = (ADC_value*3250)/(4096);//3250 is 1000 times its value for an easier displayed value
        v = Voltage;

        //weight = constant*v;
        
        sprintf(c, "%04d", v);//change weight int into char array
        msdelay(100); 
        
        I2CStart();
        I2Csendbyte(0xE2);//shows write
        msdelay(3);
        I2Csendbyte(0x76);//clears screen
        msdelay(3);
        I2Csendbyte(0x77);//change decimal command
        msdelay(3);
        I2Csendbyte(0x01);//display decimal digit, 1 for far left and so on, 4 for colon, 5 for apostraphy     more here https://github.com/sparkfun/Serial7SegmentDisplay/wiki/Special-Commands
        msdelay(3);
        I2Csendbyte(c[0]);
        msdelay(3);
        I2Csendbyte(c[1]);
        msdelay(3);
        I2Csendbyte(c[2]);
        msdelay(3);
        I2Csendbyte(c[3]);
        msdelay(3);
        
        I2CStop(); 
        msdelay(100);
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



    
   
    
 