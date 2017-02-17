#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <p33EP256MC506.h>
#define FCY 60000000ULL
#include <libpic30.h>

void main(void)
{
    TRISD = 0; // Set all port D pins as outputs
 
    // Setup UART - most default options are fine
    U1BRG = 48;            // 38400 baud @ 30 MIPS
    U1MODEbits.UARTEN = 1; // Enable UART
 
    while(1)
    {
        printf("Hello\r\n"); // Send text via UART
    }
}
    

