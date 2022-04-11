// File Name    : spi_drivers.h 
// PIC18 family, C language. 
// Dependencies : 
// Processor    : PIC18F87J11   
// Hardware     : EVB  =  PIC18 EXPLORER
//                RTCC =  MCP79410  
// I.D.E.       : MPLAB + C18 compiler   
// Company      : Microchip Technology , Inc. 
//***************************************************************************             


//---------------------------------------------------------------------------------
//                     BASIC COMMUNICATION FUNCTIONS 
//---------------------------------------------------------------------------------
void spi1_init(void)						;	// init the SPI module on MSSP1
void spi_wrbyte(unsigned char spi_data)	;	// writes a byte on the SPI bus
unsigned char spi_rdbyte (void)			;	// reads a byte from the SPI bus

