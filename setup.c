/*
 * File:   setup.c
 * Author: DT04
 *
 * Created on March 20, 2017, 3:33 PM
 */
#include <xc.h>

void UART1_init( void )
{
    /* Configure UART1 to work with RFID module*/
    
    U1MODEbits.STSEL = 0; //1-stop bit
    U1MODEbits.PDSEL = 0; //No parity, 8-bit data
    U1MODEbits.ABAUD = 0; //Auto baud rate is disabled
    U1MODEbits.BRGH = 0; //Standard baud rate
    U1BRG = 390; //Set baud rate register
    U1MODEbits.UARTEN = 1; //Enable UART
    IEC0bits.U1RXIE = 1; //Enable RX UART interrupt 
    U1STAbits.UTXEN = 1;//Set TX to Enable
    U1STAbits.URXISEL = 0b00; //Load 1 bytes in U1RXREG
    //RPINR18bits.U1RXR = 0b0110111; //Set pin 51 (RP55) to U1RX pin
    RPINR18bits.U1RXR = 0b0100111; //Set pin 46 (RP39) to U1RX
    RPOR5bits.RP54R = 0b000001; //Set pin 50 (RP54) as U1TX pin
}

void UART2_init( void )
{
    /* Configure UART2 to work with XBee*/
    
    U2MODEbits.STSEL = 0; //1-stop bit
    U2MODEbits.PDSEL = 0; //No parity, 8-bit data
    U2MODEbits.ABAUD = 0; //Auto baud rate is disabled
    U2MODEbits.BRGH = 0; //Standard baud rate
    U2BRG = 32; //Set baud rate register (115200)
    U2MODEbits.UARTEN = 1; //Enable UART
    //IEC1bits.U2RXIE = 1;
    U2STAbits.UTXEN = 1;//Set TX to Enable
    U2STAbits.URXISEL = 0b00; //Load 1 bytes in U1RXREG
    RPINR19bits.U2RXR = 0b0101100; //Set pin 62(RPI44) to U2RX pin
    RPOR4bits.RP43R = 0b000011; //Set pin 61 (RP43) to U2TX pin
}

void TIMER1_init( void )
{
    /* Configure Timer1 interrupt */
    
    _T1IP = 4; //Interrupt setup
    TMR1 = 0; //Set timer 1 to zero
    T1CON = 0x8030; //Enable timer 1 and ser prescalar to 256 
    PR1 = 2360;//creates 10[ms] timer for 60[MHz]
    //PR1= 313; //creates 10[ms] timer for 8[MHz]
    _T1IF = 0;
    _T1IE = 1;
}

void CLOCK_init( void )
{
    /* Init clock to 60[mHz] */
    
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

void LED_init( void )
{
    TRISAbits.TRISA0 = 0; //Set pin 13 (RA0) as output
    TRISDbits.TRISD8 = 0; //Set pin 42 (RD8) as output
    ANSELAbits.ANSA12=0; //Set pin 11 (RA12) as digital pin
    TRISCbits.TRISC13 = 0b1; //Set pin 47 (RC13) as input
    PORTDbits.RD8 = 1; //Set pin 42 (RD8) high for LED
}

void ADC_init( void )
{
    AD1CON1bits.ADON = 0;   //ADC1 Operation Mode (0 = ADC is off)
    AD1CON1bits.ADSIDL = 0; //Stop in idle mode (0 = continues module in Idle mode)
    AD1CON1bits.AD12B = 1;  //12-bit sampling operation (0 = disabled)
    AD1CON1bits.FORM = 0b00;    //Data output format (00 = integer)
    AD1CON1bits.SSRC = 0b111;
    AD1CON1bits.ASAM = 1;   //SAMP is auto-set
    AD1CON2 = 0x0400;
    AD1CON3bits.ADRC = 0;   //ADC1 Conversion Clock Source (0 = clock derived from system clock)
    AD1CON3bits.SAMC = 0b01111;  //Auto-sample time bits (0b01111 = 15TAD)
    AD1CON3bits.ADCS = 0b00001111;   //Conversion Clock Select
    AD1CON4 = 0x0000;
    AD1CSSH = 0x0000;
    AD1CSSL = 0x2000;
    //AD1CSSL = 0x0202;
    AD1CHS0bits.CH0SA = 0b01101;
    AD1CHS0bits.CH0NA = 0;
    AD1CON1bits.ADON = 1;
}  
