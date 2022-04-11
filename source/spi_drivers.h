// File Name    : spi_drivers.h 
// PIC18 family, C language. 
// Dependencies : 
// Processor    : PIC18F87J11   
// Hardware     : EVB  =  PIC18 EXPLORER
//                RTCC =  MCP79410  
// I.D.E.       : MPLAB + C18 compiler   
// Company      : Microchip Technology , Inc. 
// Author       : Alexandru Valeanu 
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
//                     BASIC COMMUNICATION FUNCTIONS 
//---------------------------------------------------------------------------------
void spi1_init(void)						;	// init the SPI module on MSSP1
void spi_wrbyte(unsigned char spi_data)	;	// writes a byte on the SPI bus
unsigned char spi_rdbyte (void)			;	// reads a byte from the SPI bus

