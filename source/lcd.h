 /**********************************************************************
 * FileName:        lcd.h
 * Dependencies:    none
 * Processor:       PIC24FJ128GA010 
 * Hardware:        Explorer 16 demo board, Truly TSB1G7000 LCD
 * Compiler:        MPLAB X IDE v1.41 + XC16 v1.10 C Compiler
 / *********************************************************************
 * Company:         Microchip Technology, Inc.
 *
 * Software License Agreement
 *
 * "Microchip Technology Inc." ("Microchip") licenses this software to you 
 * solely for use with Microchip's Serial RTCC products.  
 * The software is owned by Microchip and/or its licensors, and is protected 
 * under applicable copyright laws.  All rights reserved.
 *
 * SOFTWARE IS PROVIDED "AS IS."  MICROCHIP AND ITS LICENSOR EXPRESSLY 
 * DISCLAIM ANY WARRANTY OF ANY KIND, WHETHER EXPRESS OR IMPLIED, INCLUDING 
 * BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS 
 * FOR A PARTICULAR PURPOSE,OR NON-INFRINGEMENT. IN NO EVENT SHALL MICROCHIP 
 * AND ITS LICENSORS BE LIABLE FOR ANY STARTIDENTAL, SPECIAL, INDIRECT OR 
 * CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, HARM TO YOUR EQUIPMENT, 
 * COST OF PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY OR SERVICES, ANY 
 * CLAIMS BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE 
 * THEREOF), ANY CLAIMS FOR INDEMNITY OR CONTRIBUTION, OR OTHER SIMILAR COSTS."
 *
 * Author               Date       Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Alexandru Valeanu    	   Initial release for LUMEX LCD (Explorer 18 demo board)
 * Eugen Ionescu       10/04/2012  Ported to Explorer 16 demo board (Truly TSB1G7000 LCD)
 *
 ****************************************************************************************/



//*************************** LCD SIGNALS ********************************************/
#define  RW        LATDbits.LATD5     // LCD R/W signal
#define  RS        LATBbits.LATB15    // LCD RS signal
#define  E         LATDbits.LATD4     // LCD E signal 

#define  RW_TRIS   TRISDbits.TRISD5
#define  RS_TRIS   TRISBbits.TRISB15
#define  E_TRIS	   TRISDbits.TRISD4

#define  DATA      LATE               // Port for LCD data
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


//*********************** GLOBAL CONSTANTS LCD ********************************************/
#define N2_ROW1       0x00            //  start address of DDRAM ROW1 / 2 lines 
#define N2_ROW2       0x40            //  start address of DDRAM ROW2 / 2 lines
//....................................................................................... 
#define CLEAR         0x01            //  DDRAM=00h, cursor left(row1), I/D=1
#define HOME          0x02            //  DDRAM=00h, curs orig, display no shift
//.......................................................................................
#define MODE          0x04            //  entry mode (inc/dec + shift display) 
#define SHR           0x02            //  mode = shift right 
#define SHIFT         0x01            //  shift entire display
//....................................................................................... 
#define DISPLAY       0x08            //  open DISPLAY, CURSOR, BLINK 
#define D_ON          0x04            //  DISPLAY = ON 
#define C_ON          0x02            //  CURSOR  = ON 
#define B_ON          0x01            //  BLINK   = ON 
//.......................................................................................
#define CD_SHIFT      0x10            //  shift cursor or (display+cursor) 
#define CD            0x08            //  shift display+cursor 
#define RSH           0x04            //  right shift
//....................................................................................... 
#define FUNCTION      0x20            //  function set: data length, lines, fonts 
#define DL8           0x10            //  data length = 8 bits 
#define LINES         0x08            //  numer of lines = 1/2 (1 = 2L)
#define FONTS         0x04            //  type of font  
//.......................................................................................
#define SET_CGRAM     0x40            
#define SET_DDRAM     0x80            
//.......................................................................................
#define ASCII_DIGIT   0x30            //  ASCII '0' char 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~




//*********************	LCD' FUNCTIONS PROTOYPES ********************************************/
void ini_lcd(void);		      // initializes the LCD		
void wrcmnd_lcd(unsigned char cmd);   // writes command to LCD
void wrdata_lcd(unsigned char data);  // writes data to LCD
void clr_lcd(void);		      // clears LCD
void back_lcd(unsigned char pos);     // turns back cursor with 'pos' positions
void del_lcd(unsigned char pos);      // deletes back 'pos' characters
void wrstr_lcd(const char *str_lcd);	      // writes a string to LCD
void wrnr_lcd(unsigned long k);       // writes a number to LCD



