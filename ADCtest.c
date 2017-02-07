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

void initADC(void);
int getADC();
void ConfigureModuleADC(void);
void ChangeChannelADC(unsigned char CHANNEL);
float SamplingAndConversionADC(void);
void msdelay(int N);

int main(void)
{
    float ADC_value = 0;
    TRISAbits.TRISA0 = 1;
    
    ConfigureModuleADC();
    ChangeChannelADC(1);
    
    while(1)
    {
        ADC_value = SamplingAndConversionADC();
        msdelay(100);
    }
    return 0;
}
     
void ConfigureModuleADC(void)
{
    AD1CON1bits.ADON = 0;
    AD1CON3bits.ADRC = 0;
    AD1CON3bits.SAMC = 0b1111;
    AD1CON3bits.ADCS = 0b0000000;
    AD1CON2 = 0x0000;
    AD1CON1bits.ADSIDL = 0;
    AD1CON1bits.FORM = 0b00;
    AD1CON1bits.SSRC = 0;
    AD1CON1bits.ASAM = 0;
}  
    
  
void ChangeChannelADC(unsigned char CHANNEL)
{
    AD1CON1bits.ADON = 0;
    msdelay(100);
    AD1CHS0bits.CH0SA = CHANNEL;
    msdelay(100);
    AD1CON1bits.ADON = 1;
}

float SamplingAndConversionADC(void)
{
    AD1CON1bits.SAMP = 1;
    while(!AD1CON1bits.SAMP);
    AD1CON1bits.SAMP = 0;
    while(AD1CON1bits.SAMP)
    while (!AD1CON1bits.DONE);
    return(ADC1BUF0);
}
    
void _10usDelay(int N)
 {
    T2CON = 0x8000;
    TMR2 = 0;
    while(TMR2 < (16*N)){}
}
 
void msdelay(int N)
{
    T1CON=0x8030;
    double Fcyc = 16000000;
    double Tcyc = 1/Fcyc;
    double Prescaler = 256;
    double delay = N/(1000*Tcyc*Prescaler);
    TMR1=0;
    while(TMR1<=delay){}
}