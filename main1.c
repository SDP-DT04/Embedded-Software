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
#pragma config POSCMD = NONE            // Primary Oscillator Mode Select bits (EC (External Clock) Mode)
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

void I2CStart(void);
void I2CStop(void);
void I2Csendbyte(char data);
void I2Cinit(int BRG);
void ConfigureModuleADC(void);
void ChangeChannelADC(unsigned char channel);
float getADC (void);
void _10usDelay(int N);
void msdelay(int N);


int  dSec = 0, Sec = 0; // two  global  variables
void  _ISR  _T1Interrupt(void)
{
    dSec++;
    if(dSec > 2)
    {
        dSec = 0;
        Sec++;
    }
    _T1IF = 0;//clear  the  flag
}


int main(void)
{
    _T1IP = 4;
    TMR1 = 0;
    T1CON = 0x8010;
    PR1 = 16000-1;
    _T1IF = 0;
    _T1IE = 1;
      
    float ADC_value = 0;
    float Voltage = 0;
    int v = 0;
    char c[16]= {"0123456789AbCdEF"};
    int i=0;
    int j=1;
    int k=2;
    int l=3;
    TRISAbits.TRISA0 = 0;
    TRISAbits.TRISA1 = 1;
    //I2Cinit(37);
    //ConfigureModuleADC();
    //ChangeChannelADC(1);
       
    while(1)
    {
        PORTAbits.RA0 = Sec;
/*                
        ADC_value = getADC();
        Voltage = (ADC_value*3250)/(4096);
        v = Voltage;
        char c[4];
        sprintf(c, "%04d", v);
        msdelay(100); 
        
        I2CStart();
        I2Csendbyte(0xE2);
        msdelay(3);
        I2Csendbyte(0x76);
        msdelay(3);
        I2Csendbyte(c[i]);
        msdelay(3);
        I2Csendbyte(c[j]);
        msdelay(3);
        I2Csendbyte(c[k]);
        msdelay(3);
        I2Csendbyte(c[l]);
        msdelay(5000);
        I2Csendbyte(0x76);
        msdelay(3);
        
        i++;
        j++;
        k++;
        l++;
        if(i==16){i=0;}
        else if(j==16){j=0;}
        else if(k==16){k=0;}
        else if(l==16){l=0;}
        else{}
        
        I2CStop(); 
        msdelay(100);*/
    }
    return 0;
}
/*    
    float ADC_value = 0;
    float Voltage = 0;
    char c[16]= {"0123456789AbCdEF"} ;
    int i=0;
    int j=1;
    int k=2;
    int l=3;
    TRISAbits.TRISA0 = 0;
    TRISAbits.TRISA1 = 0;
    I2Cinit(37);
    ConfigureModuleADC();
    ChangeChannelADC(1);
       
    while(1)
    {
        PORTAbits.RA0 = 1;
        msdelay(250);
        PORTAbits.RA0 = 0;
        msdelay(250);
        
        ADC_value = getADC();
        Voltage = (ADC_value*3.25)/(4096);
        msdelay(100);
        
        I2CStart();
        I2Csendbyte(0xE2);
        msdelay(3);
        I2Csendbyte(0x76);
        msdelay(3);
        I2Csendbyte(c[i]);
        msdelay(3);
        I2Csendbyte(c[j]);
        msdelay(3);
        I2Csendbyte(c[k]);
        msdelay(3);
        I2Csendbyte(c[l]);
        msdelay(3);
        i++;
        j++;
        k++;
        l++;
        if(i==16){i=0;}
        else if(j==16){j=0;}
        else if(k==16){k=0;}
        else if(l==16){l=0;}
        else{}
        I2CStop(); 
        msdelay(200);
    }
    return 0;
}        
*/ 
                 
/*      sprintf(Voltagestring, "%f [V]", Voltage);

        PMADDR = 0x0000; // write command , not data
        PMDIN1 = 0xc0; // 0x0c | 0x40
        WriteString2LCD(Voltagestring);
        while(is_LCD_Busy()); // keep waiting if the LCD is busy
        while(PMMODEbits.BUSY); // wait for PMP to be available
        msdelay(50);
*/
        

    
    /*
    while(1){
        I2CStart();
        I2Csendbyte(0xE2);
        msdelay(3);
        I2Csendbyte(0x76);
        msdelay(3);
        I2Csendbyte(voltage[1]);
        msdelay(3);
        I2Csendbyte(voltage[2]);
        msdelay(3);
        I2Csendbyte(voltage[3]);
        msdelay(3);
        I2Csendbyte(voltage[4]);
        msdelay(3);
        
    }
    */
    
 /*
     //7Seg I2C Example Code
    char c[16]= {"0123456789AbCdEF"} ;
    I2Cinit(37);
    int i=0;
    int j=1;
    int k=2;
    int l=3;
       while(1){
        I2CStart();
        I2Csendbyte(0xE2);
        msdelay(3);
        I2Csendbyte(0x76);
        msdelay(3);
        I2Csendbyte(c[i]);
        msdelay(3);
        I2Csendbyte(c[j]);
        msdelay(3);
        I2Csendbyte(c[k]);
        msdelay(3);
        I2Csendbyte(c[l]);
        msdelay(3);
        i++;
        j++;
        k++;
        l++;
        if(i==16){
            i=0;
        }else if(j==16){
            j=0;
        }else if(k==16){
            k=0;
        }else if(l==16){
            l=0;
        }else{
        }
       
        I2CStop(); 
        msdelay(500);
    }
*/
    //return 0;
//}

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

void ConfigureModuleADC(void)
{
    AD1CON1bits.ADON = 0;   //ADC1 Operation Mode (0 = ADC is off)
    AD1CON3bits.ADRC = 0;   //ADC1 Conversion Clock Source (0 = clock derived from system clock)
    AD1CON3bits.SAMC = 0b1111;  //Auto-sample time bits (0b1111 = 15TAD)
    AD1CON3bits.ADCS = 0b0000000;   //Conversion Clock Select
    AD1CON2 = 0x0000;
    AD1CON4 = 0x0000;
    AD1CON1bits.AD12B = 1;  //12-bit sampling operation (1 = enabled)
    AD1CON1bits.ADSIDL = 0; //Stop in idle mode (0 = continues module in Idle mode)
    AD1CON1bits.FORM = 0b00;    //Data output format (00 = integer)
    AD1CON1bits.SSRC = 0;
    AD1CON1bits.ASAM = 0;   //Sampling begins when SAMP is set
    
    /*
    AD1CON1 = 0x00E0; //Turn off , auto  sample , auto  start , auto  convert
    AD1CON2 = 0x0000; //AVdd , AVss , int  every  conversion , MUXA  only
    AD1CON3 = 0x1F05; //auto -sample , Tad = 5 Tcy
    AD1CON4 = 0x0000;
    AD1CSSL = 0;      // ignore  all on scan  select
    TRISBbits.TRISB5 = 1;   //  Enable  the  pin to  potentiometer  as ADC  input
    AD1PCFGbits.PCFG5;      // disable  PORTB5  as a digital  input
    AD1CON1bits.ADON = 1;   //turn on AD
    */
}  
    
  
void ChangeChannelADC(unsigned char channel)
{
    AD1CON1bits.ADON = 0;   //ADC1 Operation Mode (0 = ADC is off)
    msdelay(100);
    AD1CHS0bits.CH0SA = channel;    //Channel 0 +input for MUXA (0-15 = channel)
    msdelay(100);
    AD1CON1bits.ADON = 1;   //ADC1 Operation Mode (1 = ADC is on)
}

float getADC(void)
{
    AD1CON1bits.SAMP = 1;   //ADC1 Sample enable (1 = sampling)
    while(!AD1CON1bits.SAMP); 
    AD1CON1bits.SAMP = 0;   //ADC1 Sample enable (0 = holding)
    while(AD1CON1bits.SAMP)
    while (!AD1CON1bits.DONE);  //ADC1 Conversion Status (0 = not started/in progress, 1 = completed)
    return(ADC1BUF0);   //ADC1BUF0 = AN0 data buffer
}