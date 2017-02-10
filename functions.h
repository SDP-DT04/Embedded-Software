/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_FUNCTIONS_H
#define	XC_FUNCTIONS_H

void I2CStart(void);
void I2CStop(void);
void I2Csendbyte(char data);
void I2Cinit(int BRG);
void ConfigureModuleADC(void);
void ChangeChannelADC(unsigned char channel);
void display(char c[], int dec);
void ConfigureClock(void);
void ConfigureClockSlow(void);


#include <xc.h> // include processor files - each processor file is guarded.  
#define FCY 8000000ULL
#include <libpic30.h>

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

void I2CStart(void)
{
    __delay_us(10);
    I2C2CONbits.SEN = 1;
    while (I2C2CONbits.SEN);
    __delay_us(10);
}

void I2CStop(void)
{
    __delay_us(10);
    I2C2CONbits.PEN = 1;
    while (I2C2CONbits.PEN);
    __delay_us(10);
}

void I2Csendbyte(char data)
{
    while (I2C2STATbits.TBF);
    I2C2TRN = data;
    __delay_us(10);
}

void I2Cinit(int BRG)
{
    I2C2BRG = BRG;
    I2C2CONbits.I2CEN = 1;
}

void display(char c[], int dec)
{
    I2CStart();
    I2Csendbyte(0xE2);//shows write
    __delay_us(200);
    I2Csendbyte(0x76);//clears screen
    __delay_us(200);
    I2Csendbyte(0x77);//change decimal command
    __delay_us(200);
    I2Csendbyte(dec);//display decimal digit, 1 for far left, 2 for next, 4 for the next, 8 for next, 16 for colon, 32 for apostraphy     more here https://github.com/sparkfun/Serial7SegmentDisplay/wiki/Special-Commands
    __delay_us(200);
    I2Csendbyte(c[0]);
    __delay_us(200);
    I2Csendbyte(c[1]);
    __delay_us(200);
    I2Csendbyte(c[2]);
    __delay_us(200);
    I2Csendbyte(c[3]);
    __delay_us(200);    
    I2CStop(); 
    //1.68ms delay
}

// void _10usDelay(int N)
// {
//    T2CON = 0x8000;
//    TMR2 = 0;
//    while(TMR2 < (16*N)){}
//}
 
//void msdelay(int N)
//{
//    T1CON=0x8030;
//    double Fcyc = 60000000;
//    double Tcyc = 1/Fcyc;
//    double Prescaler = 256;
//    double delay = N/(1000*Tcyc*Prescaler);
//    TMR1=0;
//    while(TMR1<=delay){}
//}

void ConfigureModuleADC(void)
{
    AD1CON1bits.ADON = 0;   //ADC1 Operation Mode (0 = ADC is off)
    AD1CON1bits.ADSIDL = 0; //Stop in idle mode (0 = continues module in Idle mode)
    AD1CON1bits.AD12B = 1;  //12-bit sampling operation (0 = disabled)
    AD1CON1bits.FORM = 0b00;    //Data output format (00 = integer)
    AD1CON1bits.SSRC = 0b111;
    AD1CON1bits.ASAM = 1;   //SAMP is auto-set
    AD1CON2 = 0x0404;
    AD1CON3bits.ADRC = 0;   //ADC1 Conversion Clock Source (0 = clock derived from system clock)
    AD1CON3bits.SAMC = 0b01111;  //Auto-sample time bits (0b01111 = 15TAD)
    AD1CON3bits.ADCS = 0b00001111;   //Conversion Clock Select
    AD1CON4 = 0x0000;
    AD1CSSH = 0x0000;
    AD1CSSL = 0x0200;
    //AD1CSSL = 0x0202;
    AD1CHS0bits.CH0SA = 0;
    AD1CHS0bits.CH0NA = 0;
    AD1CON1bits.ADON = 1;
    __delay_us(20);
}  
    
void ChangeChannelADC(unsigned char channel)
{
    AD1CON1bits.ADON = 0;   //ADC1 Operation Mode (0 = ADC is off)
    __delay_ms(100);
    AD1CHS0bits.CH0SA = channel;    //Channel 0 +input for MUXA (0-15 = channel)
    __delay_ms(100);
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

void ConfigureClock(void)
{
/*  FRC (default) = 7.37[MHz]
    Fosc = (FRC*M)/[FRCDIV*(N1*N2)]
    M = PLLFBDbits.PLLDIV + 2
    N1 = CLKDIVbits.PLLPRE + 2
    N2 = 2*(CLKDIVbits.PLLPOST + 1)
    Fosc = [(7.37E6)*(65)]/[1*(2*2)] = 119.7625[MHz]
    Fcyc = Fosc/2 = 59.88125[MHz] ? 60[MHz]
*/
    //Configure OSSCON
    OSCCONbits.COSC = 0b001; //Sets Oscillator in mode with FRC, divide by N, and PLL mode
    OSCCONbits.NOSC = 0b001; //Sets new Oscillator in mode with FRC, divide by N, and PLL mode
    OSCCONbits.CLKLOCK = 0b0; //Clock Lock Enable bit (0 = may be modified)
    OSCCONbits.IOLOCK = 0b0; //I/O Lock Enable bit (0 = I/O lock is not active)
    OSCCONbits.LOCK = 0b1; //PLL Lock Status bit (1 = PLL in lock or start-up timer is satisfied)
    
    //Configure CLKDIV
    CLKDIVbits.ROI = 0; //Recover on Interrupt bit (0 = Interrupts have no effect on the DOZEN bit)
    CLKDIVbits.DOZE = 0; //Processor Clock Reduction Select bits (000 = Fcy/1)
    CLKDIVbits.DOZEN = 0; //Doze Mode Enable bit (0 = Fcy=Fp)
    CLKDIVbits.FRCDIV = 0b000; //Internal Fast RC Oscillator Postscaler bits (0 = 1)
    CLKDIVbits.PLLPOST = 0b00; //PLL VCO Output Divider Select bits (N2)
    CLKDIVbits.PLLPRE = 0b00000; //PLL Phase Detector Input Divider Select bits (N1)
    
    //Configure PLLFBD
    PLLFBDbits.PLLDIV = 0b000111111; //{63} PLL Feedback Divisor bits (M)
    
    //Configure OSCTUN
    OSCTUNbits.TUN = 0b00100; //FRC Oscillator Tuning bits (4 = (FRC = 7.3838[MHz]) 
}

void ConfigureClockSlow(void)
{
/*  FRC (default) = 7.37[MHz]
    Fosc = (FRC*M)/[FRCDIV*(N1*N2)]
    M = PLLFBDbits.PLLDIV + 2
    N1 = CLKDIVbits.PLLPRE + 2
    N2 = 2*(CLKDIVbits.PLLPOST + 1)
    Fosc = [(7.37E6)*(65)]/[1*(2*2)] = 119.7625[MHz]
    Fcyc = Fosc/2 = 59.88125[MHz] ? 60[MHz]
*/
    //Configure OSSCON
    OSCCONbits.COSC = 0b001; //Sets Oscillator in mode with FRC, divide by N, and PLL mode
    OSCCONbits.NOSC = 0b001; //Sets new Oscillator in mode with FRC, divide by N, and PLL mode
    OSCCONbits.CLKLOCK = 0b0; //Clock Lock Enable bit (0 = may be modified)
    OSCCONbits.IOLOCK = 0b0; //I/O Lock Enable bit (0 = I/O lock is not active)
    OSCCONbits.LOCK = 0b1; //PLL Lock Status bit (1 = PLL in lock or start-up timer is satisfied)
    
    //Configure CLKDIV
    CLKDIVbits.ROI = 0; //Recover on Interrupt bit (0 = Interrupts have no effect on the DOZEN bit)
    CLKDIVbits.DOZE = 0; //Processor Clock Reduction Select bits (000 = Fcy/1)
    CLKDIVbits.DOZEN = 0; //Doze Mode Enable bit (0 = Fcy=Fp)
    CLKDIVbits.FRCDIV = 0b001; //Internal Fast RC Oscillator Postscaler bits (0 = 1)
    CLKDIVbits.PLLPOST = 0b00; //PLL VCO Output Divider Select bits (N2)
    CLKDIVbits.PLLPRE = 0b00000; //PLL Phase Detector Input Divider Select bits (N1)
    
    //Configure PLLFBD
    PLLFBDbits.PLLDIV = 0b000001110; //{63} PLL Feedback Divisor bits (M)
    
    //Configure OSCTUN
    OSCTUNbits.TUN = 0b00100; //FRC Oscillator Tuning bits (4 = (FRC = 7.3838[MHz]) 
}

