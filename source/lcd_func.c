// File Name    : lcd_func.c 
// PIC24 family, C language. 
// Dependencies : p24fj128ga010.h, delay.h, lcd.h 
// Processor    : PIC24FJ128GA010    
// Hardware     : Explorer 16 demo board, Truly TSB1G7000 LCD
// I.D.E.       : MPLAB X IDE v1.41 + XC16 v1.10 C Compiler
/***********************************************************************
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
* Author            Date          Comment
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*
* Eugen Ionescu     10/04/2012    Initial release for Explorer 16 demo board (Truly TSB1G7000 LCD)
* Florian Gheorghe  22/09/2015    Replaced custom delay functions with the ones recommended by 16-Bit_Language_Tools_Libraries_Manual;
*                                 Replaced header file p24fj128ga010.h with xc.h  
*************************************************************************************************/

#define FCY 32000000UL

#include "xc.h"
#include "libpic30.h"
#include "lcd.h"




//................................................................................................
//                       LCD LOW LEVEL FUNCTIONS 
//................................................................................................   
void ini_lcd(void)                     
{
__delay_ms(15); __delay_ms(15); // wait Vdd reaches nnVdc before proceeding with LCD initialization)

// set initial states for the data & control pins 
DATA &= 0xFF00;		      // clear RE0-RE7 (data pins)
RW = 0;                       // R/W = low
RS = 0;                       // RS = low
E = 0;                        // E = low

// set data & control pins to outputs 
TRISE &= 0xFF00;              // RE0 - RE7 = output (data pins)
RW_TRIS = 0;                  // RW = output
RS_TRIS = 0;                  // RS = output
E_TRIS = 0;                   // E = output

wrcmnd_lcd(FUNCTION+DL8+LINES);// function set (data length = 8 bits, 2 lines)
wrcmnd_lcd(DISPLAY+D_ON);     // Display = ON, cursor & blink = OFF 
wrcmnd_lcd(MODE+SHR);         // entry mode set (inc mode, shift right)
}    


//....................................................................................
//                      Writes command to LCD
//....................................................................................
void wrcmnd_lcd(unsigned char cmd)  
{
DATA &= 0xFF00;               // clear RE0-RE7 (data pins)
DATA |= cmd;                  // send command byte to LCD
RW = 0;                       // ensure RW is 0
RS = 0;                       // and RS is 0
E = 1;                        // toggle E signal
Nop();
Nop();
Nop();
E = 0;                        // clear E signal
__delay_ms(5);                   // 5ms delay
}


//....................................................................................
// 			Writes data to LCD
//....................................................................................
void wrdata_lcd(unsigned char data)   
{
RW = 0;       		      // ensure RW is 0
RS = 1;                       // assert register select to 1
DATA &= 0xFF00;               // clear RE0-RE7 (data pins)
DATA |= data;                 // send data byte to lcd
E = 1;			      // set E signal
Nop();
Nop();
Nop();
E = 0;                        // toggle E signal
RS = 0;                       // negate register select to 0
__delay_us(200);              // 200uS delay
__delay_us(200);              // 200uS delay
}  

//....................................................................................
// 		Clears the LCD, cursor left up corner on first row
//....................................................................................
void clr_lcd(void)               	
{
wrcmnd_lcd(CLEAR);	      // CLEAR command
__delay_ms(15);           // 15ms delay
}

//....................................................................................
//                  Turns back cursor with 'pos' positions
//....................................................................................
void back_lcd(unsigned char pos)     
{
while(pos)                    // for 'pos' positions
	{
	wrcmnd_lcd(CD_SHIFT); // shift left cursor
	pos--; 
	}
}      

//....................................................................................
// 			Deletes back 'pos' characters
//....................................................................................
void del_lcd(unsigned char pos)     
{

unsigned char k = 0;          // loop counter
wrcmnd_lcd(DISPLAY+D_ON);     // CURSOR = OFF, Blink = ON
back_lcd(pos);		      // shift left cursor for 'pos' positions
k=pos;
while(pos)
	{
	wrdata_lcd(' ');      // delete 'pos' characters
	pos--;
	}
back_lcd(k);                  // shift left cursor for 'pos' positions
wrcmnd_lcd(DISPLAY+D_ON+C_ON); // display & cursor & blink = ON
}  




//****************** LCD HIGH LEVEL FUNCTIONS ****************************************

//....................................................................................
// 		  	 Writes a string to LCD
//....................................................................................
void wrstr_lcd(const char *str) 
{
while(*str)                   // loop till the end of the string
	{
	wrdata_lcd(*str);     // display string's char
	str++;
	} 	  
}  			  

//...................................................................................................
// 		    	 Writes a number to LCD
//...................................................................................................
void wrnr_lcd(unsigned long k)             
{
unsigned char v[12];         // stores the digits of a number
int i=0;                     // stores how many digits has a number

if (k>0)                     // if the number > 0 
	{
	while (k)            // find the digits' number until becomes 0
		{                                  
		v[i]=(k%10); // store the digit
		k=k/10;      // divide the number with 10 (eliminate the last digit)
		i++;         // inc the digits counter
		}

	i--;                 // dec the digits counter (the vector has i-1 elements)
	for (;i>=0;i--)  wrdata_lcd((v[i])+ASCII_DIGIT);  // display the number on LCD
	}
else wrdata_lcd(0+ASCII_DIGIT); // display 0 value 
}





