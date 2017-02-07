/*
 * File:   main1.c
 * Author: DT04
 *
 * Created on December 13, 2016, 2:55 PM
 */

// FICD
#pragma config ICS = PGD3               // ICD Communication Channel Select bits (Communicate on PGEC3 and PGED3)
#pragma config JTAGEN = OFF             // JTAG Enable bit (JTAG is disabled)

// FPOR
#pragma config ALTI2C1 = OFF            // Alternate I2C1 pins (I2C1 mapped to SDA1/SCL1 pins)
#pragma config ALTI2C2 = OFF            // Alternate I2C2 pins (I2C2 mapped to SDA2/SCL2 pins)
#pragma config WDTWIN = WIN25           // Watchdog Window Select bits (WDT Window is 25% of WDT period)

// FWDT
#pragma config WDTPOST = PS32768        // Watchdog Timer Postscaler bits (1:32,768)
#pragma config WDTPRE = PR128           // Watchdog Timer Prescaler bit (1:128)
#pragma config PLLKEN = ON              // PLL Lock Enable bit (Clock switch to PLL source will wait until the PLL lock signal is valid.)
#pragma config WINDIS = OFF             // Watchdog Timer Window Enable bit (Watchdog Timer in Non-Window mode)
#pragma config FWDTEN = ON              // Watchdog Timer Enable bit (Watchdog timer always enabled)

// FOSC
#pragma config POSCMD = NONE              // Primary Oscillator Mode Select bits (EC (External Clock) Mode)
#pragma config OSCIOFNC = OFF           // OSC2 Pin Function bit (OSC2 is clock output)
#pragma config IOL1WAY = ON             // Peripheral pin select configuration (Allow only one reconfiguration)
#pragma config FCKSM = CSDCMD           // Clock Switching Mode bits (Both Clock switching and Fail-safe Clock Monitor are disabled)

// FOSCSEL
#pragma config FNOSC = FRCDIVN          // Oscillator Source Selection (Internal Fast RC (FRC) Oscillator with postscaler)
#pragma config PWMLOCK = ON             // PWM Lock Enable bit (Certain PWM registers may only be written after key sequence)
#pragma config IESO = ON                // Two-speed Oscillator Start-up Enable bit (Start up device with FRC, then switch to user-selected oscillator source)

// FGS
#pragma config GWRP = OFF               // General Segment Write-Protect bit (General Segment may be written)
#pragma config GCP = OFF                // General Segment Code-Protect bit (General Segment Code protect is Disabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.


#include <xc.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define BUS_FRQ 100000L


void I2CStart(void);
void I2CStop(void);
void I2Csendbyte(char data);
void I2Cinit(int BRG);
void ms_delay(int N);
void _10usDelay(int N);

int main(void) {
    char c[16]= {"0123456789AbCdEF"} ;
    I2Cinit(9600);
    
    I2CStart();   
    I2Csendbyte(0xE0); //Address
    ms_delay(3);
    I2Csendbyte(0x21); //Clock turn on
    ms_delay(3);
    I2CStop();
    ms_delay(1);
    
//    I2CStart();    
//    I2Csendbyte(0xE0); //Address
//    ms_delay(3);    
//    I2Csendbyte(0xA0); //ACT ROW/INT
//    ms_delay(3);
//    I2CStop();
//    ms_delay(1);
    
    I2CStart();    
    I2Csendbyte(0xE0); //Address
    ms_delay(3);
    I2Csendbyte(0xE0); //EF MAX Brightness
    ms_delay(3);
    I2CStop();
    ms_delay(1);
    
    I2CStart();    
    I2Csendbyte(0xE0); //Address
    ms_delay(3);    
    I2Csendbyte(0x80); //Display on with no blink
    ms_delay(3);
    I2CStop();
    ms_delay(1);
    
    while(1){
    I2CStart();    
    I2Csendbyte(0xE0); //Address
    ms_delay(3);    
    I2Csendbyte(0x00); //show 0
    ms_delay(3);
    I2Csendbyte(0xAA);
    ms_delay(3);
    I2CStop();
    ms_delay(50);    
    }
    int i=0;
    int j=1;
    int k=2;
    int l=3;
//while(1)
//{
//    I2CStart();    
//    I2Csendbyte(0xE0); //Address
//    
//    I2Csendbyte(c[i]);
//    ms_delay(3);
//    I2Csendbyte(c[j]);
//    ms_delay(3);
//    I2Csendbyte(c[k]);
//    ms_delay(3);
//    I2Csendbyte(c[l]);
//    ms_delay(3);
//    
//    i++;
//    j++;
//    k++;
//    l++;
//    if(i==16){
//        i=0;
//    }else if(j==16){
//        j=0;
//    }else if(k==16){
//        k=0;
//    }else if(l==16){
//         l=0;
//    }else{
//    }
//       
//    I2CStop(); ms_delay(500);
//    }
    return 0;
}
void I2CStart(void)
{
    _10usDelay(1);
    I2C1CONbits.SEN = 1;
    while (I2C1CONbits.SEN);
    _10usDelay(1);
}
void I2CStop(void)
{
    _10usDelay(1);
    I2C1CONbits.PEN = 1;
    while (I2C1CONbits.PEN);
    _10usDelay(1);
}
void I2Csendbyte(char data)
{
    while (I2C1STATbits.TBF);
    I2C1TRN = data;
    _10usDelay(1);
}
void I2Cinit(int BRG)
{
    I2C1BRG = BRG;
    I2C1CONbits.I2CEN = 1;
 
}
void ms_delay(int N){
    T1CON = 0b1000000000110000;
    double Fcyc = 16000000;
    double Tcyc = 1/Fcyc;
    double Prescaler = 256;
    double delay = N/(1000*Tcyc*Prescaler);
    TMR1 = 0;
    while(TMR1 <= delay) {}
}
 void _10usDelay(int N){
    T2CON = 0x8000;
    TMR2 = 0;
    while(TMR2 < (16*N)){}
}