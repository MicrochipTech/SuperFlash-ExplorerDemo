// File Name    : spi_drivers.h 
// PIC18 family, C language. 
// Dependencies :	spi_drivers.h
// Processor    :	PIC18F87J11   
// Hardware     :	EVB  =  PIC18 EXPLORER
//               	RTCC =  MCP79410  
// I.D.E.       :	MPLAB + C18 compiler   
// Company      :	Microchip Technology , Inc. 
// Author       :	Alexandru Valeanu 
//...........................................................................
//                   SOFTWARE  LICENSE AGREEMENT    
//...........................................................................
// "Microchip Technology Inc." ("Microchip") licenses this software to you 
// solely for use with Microchip's Serial RTCC products.  
// The software is owned by Microchip and/or its licensors, and is protected 
// under applicable copyright laws.  All rights reserved.
// SOFTWARE IS PROVIDED "AS IS."  MICROCHIP AND ITS LICENSOR EXPRESSLY 
// DISCLAIM ANY WARRANTY OF ANY KIND, WHETHER EXPRESS OR IMPLIED, INCLUDING 
// BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS 
// FOR A PARTICULAR PURPOSE,OR NON-INFRINGEMENT. IN NO EVENT SHALL MICROCHIP 
// AND ITS LICENSORS BE LIABLE FOR ANY INCIDENTAL, SPECIAL, INDIRECT OR 
// CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, HARM TO YOUR EQUIPMENT, 
// COST OF PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY OR SERVICES, ANY 
// CLAIMS BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE 
// THEREOF), ANY CLAIMS FOR INDEMNITY OR CONTRIBUTION, OR OTHER SIMILAR COSTS."
//***************************************************************************          


//---------------------------------------------------------------------------------
//				DEPENDENCIES
//---------------------------------------------------------------------------------
//#include "p18f87j11.h"
#include "xc.h"
#include "stdint.h"
#include "libpic30.h"
#include "stdlib.h"
#include <p24Fxxxx.h>
#include "spi_drivers.h"
//---------------------------------------------------------------------------------
//				BASIC COMMUNICATION FUNCTIONS 
//---------------------------------------------------------------------------------
void spi1_init(void)					//	init the SPI module on MSSP1
{
    // SDI to pin #11 AN18/C1INC/RP26/OCM1B/PMA4/RG7
    // SDO to pin #12 AN19/C2IND/RP19/OCM2A/PMA3/RG8
    // SCK to pin #10 AN17/C1IND/RP21/OCM1A/PMA5/RG6
    _SDI1R = 26; // SDI input to RG7/RP26    
    _ANSG7 = 0;  // digital input
    _RP19R = 7;  // SDO output (option 7) to RG8/RP19
    _RP21R = 8;  // SCK output (option 8) to RG6/RP21    
    _SCK1R = 21; // SCK input  
    _ANSG6 = 0;  // digital input    
    
    // Chip select to pin #79 RPI42/OCM3E/PMD12/RD12 PIM jumpers must be set to EPMP
    _LATG9 = 1;
    _TRISG9 = 0; // EEPROM CS is output

    SPI1CON2 = 0;
    SPI1CON1 = 0;
    SPI1BRGL = 0;
    SPI1BRGL = 8; // 0 = FCY/2 = 8MHz, 2 = ???
    SPI1CON1bits.MSTEN = 1;
    SPI1CON1bits.MODE16 = 0; // 8 -bit
    SPI1CON1bits.SMP=0;
    SPI1CON1bits.CKE=1;
    SPI1CON1bits.CKP=0; // SPI mode 0
    SPI1CON1bits.SPIEN = 1;
}
	
void spi_wrbyte(unsigned char spi_data) // writes a byte on the SPI bus (for LCD)
{
    char aux;
    SPI1BUFL = spi_data;
    while (!SPI1STATLbits.SPIRBF);
    aux = SPI1BUFL;
}
	
unsigned char spi_rdbyte (void)
{
    unsigned char aux;
    SPI1BUFL = 0x00;
    while (!SPI1STATLbits.SPIRBF);
    aux = SPI1BUFL;
    return SPI1BUFL;
}
