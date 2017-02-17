/*
 * File:   RFID.c
 * Author: DT04
 *
 * Created on February 16, 2017, 1:05 PM
 */

#include "config.h"
#include "functions.h"
#include <xc.h>
#include  <stdbool.h>
#include <p33EP256MC506.h>
#include <string.h>
#define FCY 60000000ULL
//#define FCY 8000000ULL
#include <libpic30.h>

char ReceivedChar[16] = {"0000000000000000"};
int i = 0, j = 0, k = 0, m = 0, n = 0;
const int tagLen = 16;
const int idLen = 13; //idLen = 13  because 12 data plus NULL
const int kTags = 4; //total number of tags
char nTag[12];
char oTag[12];
char knownTags[12] = {"82003BE82372"};

char newTag[16]; //idLen = 13  because 12 data plus NULL
char tagData[12];
char test[12] = {"82003BE82372"};
//test[0] = 0x02;
//test[13] = 0x0D;
//test[14] = 0x0A;
//test[15] = 0x03;


int main(void)
{
    ConfigureClock();
    TRISAbits.TRISA0 = 0;
    TRISDbits.TRISD8 = 0;
    U1MODEbits.STSEL = 0; //1-stop bit
    U1MODEbits.PDSEL = 0; //No parity, 8-bit data
    U1MODEbits.ABAUD = 0; //Auto baud rate is disabled
    U1MODEbits.BRGH = 0; //Standard baud rate
    
    U1BRG = 390; //set baud rate register
    
    U1STAbits.URXISEL = 0b11; //load 4 bytes in U1RXREG
    
    U1MODEbits.UARTEN = 1; //Enable UART
    
    RPINR18bits.U1RXR = 0b0100111; //Set pin 46 (RP39) to U1RX pin
    PORTDbits.RD8 = 1;
    //LATDbits.LATD8 = 1;
    
//    while(1)
//    { 
//        for (k = 0; k<17; k++)
//        {
//            if(U1STAbits.FERR == 1) //Check for receive errors
//            {
//                continue;
//            }
//
//            if(U1STAbits.OERR == 1) //Clear overrun error to keep UART receiving
//            {
//                U1STAbits.OERR = 0;
//                continue;
//            }
//
//            if(U1STAbits.URXDA == 1) //Get the data
//            {
//                ReceivedChar[k] = U1RXREG;
//            }
//        }
////        if(ReceivedChar = data)
//    }
//    return 0;
    while(1)
        {
        m = 0;
            int readByte; //Variable to hold each byte read from the serial buffer
            bool tag = false; //Flag so we know when a tag is over
        
//            for (i = 0; i<17; i++)
//            {
//                tagData[i] = U1RXREG;
//            }
//            
//             for (j = 0; j<idLen; j++)
//            {
//                tagData[j++] = test[j];
//            }
            tag == true;
            k = 0;
            if (tag == true) 
            {
                while (!U1STAbits.URXDA)
                {
                    if (k<17)
                    {
                        readByte = U1RXREG; //Take each byte out of the serial buffer, one at a time
                        //readByte = test[m];
                                 
                        if (readByte != 2 && readByte!= 13 && readByte != 10 && readByte != 3)
                        {
                            newTag[m] = readByte;
                            m++;
                        }
                        
                        for (n = 0; n<idLen; n++)
                        {
                            tagData[n] = newTag[n+1];
                        }

                        if (k == 16) //If we see ASCII 3, ETX, the tag is over
                        {
                            tag == false;
                        }
                        k++;
                    }
                }
            }
            
            if (strlen(newTag)== 0) //don't do anything if the newTag array is full of zeroes
            {
                return;
            }

            else 
            {
                int total = 0;
                                
                total += checkTag(tagData, knownTags);
                

                if (total > 0) // If newTag matched any of the tag swe checked against, total will be 1
                {
                    //LATDbits.LATD8 = 0;
                    PORTDbits.RD8 = 0;
                }

                else 
                {
                    //LATDbits.LATD8 = 1;
                    //PORTDbits.RD8 = 1;
                }
            }
        }
    }
int checkTag(char nTag[12], char oTag[12])
{
    for (i = 0; i < idLen; i++)
    {
        if (nTag[i] != oTag[i])
        {
            return 0;
        }
    }
    return 1;
}
///*----------------------------------------------------------------------------*/
//// For SparkFun's tags, we will receive 16 bytes on every
//// tag read, but throw four away. The 13th space will always
//// be 0, since proper strings in Arduino end with 0
//
//// These constants hold the total tag length (tagLen) and
//// the length of the part we want to keep (idLen),
//// plus the total number of tags we want to check against (kTags)
//const int tagLen = 16;
//const int idLen = 13; //idLen = 13  because 12 data plus NULL
//const int kTags = 4; //total number of tags
//
//// Put your known tags here!
//char knownTags[kTags][idLen] =
//{
//    "82003BE82372",
//    "82003BBE0106",
//    "555555555555",
//    "7A005B0FF8D6"
//};
//
//// Empty array to hold a freshly scanned tag
//char newTag[idLen]; //idLen = 13  because 12 data plus NULL
//char tagData[];
//void loop() 
//{
//  // Counter for the newTag array
//  int i = 0;
//  int j = 0;
//  // Variable to hold each byte read from the serial buffer
//  int readByte;
//  // Flag so we know when a tag is over
//  bool tag = false;
//
//  // This makes sure the whole tag is in the serial buffer before
//  // reading, the Arduino can read faster than the ID module can deliver!
////  if (rSerial.available() == tagLen) 
////  {
////    tag = true;
////  }
//  
//    for (j = 0; j<17; j++)
//    {
//        tagData[j] = U1RXREG;
//    }
//    if (strlen(tagData) != 16)
//    {
//        tag = true;
//    }
//
//  if (tag == true) 
//  {
//    while (!U1STAbits.URXDA)
//    {
//      // Take each byte out of the serial buffer, one at a time
//      readByte = U1RXREG;
//
//      /* This will skip the first byte (2, STX, start of text) and the last three,
//      ASCII 13, CR/carriage return, ASCII 10, LF/linefeed, and ASCII 3, ETX/end of 
//      text, leaving only the unique part of the tag string. It puts the byte into
//      the first space in the array, then steps ahead one spot */
//      if (readByte != 2 && readByte!= 13 && readByte != 10 && readByte != 3)
//      {
//        newTag[i] = readByte;
//        i++;
//      }
//
//      // If we see ASCII 3, ETX, the tag is over
//      if (readByte == 3) 
//      {
//        tag = false;
//      }
//
//    }
//  }
//
//
//  // don't do anything if the newTag array is full of zeroes
//  if (strlen(newTag)== 0) 
//  {
//    return;
//  }
//
//  else 
//  {
//    int total = 0;
//    int ct = 0;
//
//    for (ct=0; ct < kTags; ct++)
//    {
//        total += checkTag(newTag, knownTags[ct]);
//    }
//
//    // If newTag matched any of the tags
//    // we checked against, total will be 1
//    if (total > 0) 
//    {
//        PORTAbits.RA0 = 1;
//    }
//
//    else 
//    {
//        PORTAbits.RA0 = 1;
//    }
//  }
//
//}