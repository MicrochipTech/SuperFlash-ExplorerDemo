/*
CODE OWNERSHIP AND DISCLAIMER OF LIABILITY

Microchip Technology Incorporated ("Microchip") retains all ownership and
intellectual property rights in the code accompanying this message and in all
derivatives hereto. You may use this code, and any derivatives created by any
person or entity by or on your behalf, exclusively with Microchip?s proprietary
products. Your acceptance and/or use of this code constitutes agreement to the
terms and conditions of this notice.

CODE ACCOMPANYING THIS MESSAGE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES,
WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED
WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY AND FITNESS FOR A PARTICULAR
PURPOSE APPLY TO THIS CODE, ITS INTERACTION WITH MICROCHIP?S PRODUCTS,
COMBINATION WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

YOU ACKNOWLEDGE AND AGREE THAT, IN NO EVENT, SHALL MICROCHIP BE LIABLE, WHETHER
IN CONTRACT, WARRANTY, TORT (INCLUDING NEGLIGENCE OR BREACH OF STATUTORY DUTY),
STRICT LIABILITY, INDEMNITY, CONTRIBUTION, OR OTHERWISE, FOR ANY INDIRECT,
SPECIAL, PUNITIVE, EXEMPLARY, INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, FOR COST
OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE CODE, HOWSOEVER CAUSED, EVEN IF
MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO
THE FULLEST EXTENT ALLOWABLE BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS
IN ANY WAY RELATED TO THIS CODE, SHALL NOT EXCEED THE PRICE YOU PAID DIRECTLY TO
MICROCHIP SPECIFICALLY TO HAVE THIS CODE DEVELOPED.

You agree that you are solely responsible for testing the code and determining
its suitability.  Microchip has no obligation to modify, test, certify, or
support the code.


File description:
 Main file for Simplified Flash Demo. Measures the time required to fully erase 
 a flash device.

Revision history:
 v1.0 - First version, October, 2015
      - tested with XC16 v1.24
 
 v1.1 - 2015-10-22
      - added SST26VF016B, SST26WF080B, SST26WF040B
      - converted msec variable from uint16_t to uint32_t
 v2.0 - 2018-12-11
 *    - Converted to PIC24FJ1034GB610
 */


// FSEC
#pragma config BWRP = OFF               // Boot Segment Write-Protect bit (Boot Segment may be written)
#pragma config BSS = DISABLED           // Boot Segment Code-Protect Level bits (No Protection (other than BWRP))
#pragma config BSEN = OFF               // Boot Segment Control bit (No Boot Segment)
#pragma config GWRP = OFF               // General Segment Write-Protect bit (General Segment may be written)
#pragma config GSS = DISABLED           // General Segment Code-Protect Level bits (No Protection (other than GWRP))
#pragma config CWRP = OFF               // Configuration Segment Write-Protect bit (Configuration Segment may be written)
#pragma config CSS = DISABLED           // Configuration Segment Code-Protect Level bits (No Protection (other than CWRP))
#pragma config AIVTDIS = OFF            // Alternate Interrupt Vector Table bit (Disabled AIVT)

// FBSLIM
#pragma config BSLIM = 0x1FFF           // Boot Segment Flash Page Address Limit bits (Boot Segment Flash page address  limit)

// FSIGN

// FOSCSEL
#pragma config FNOSC = FRCPLL           // Oscillator Source Selection (Fast RC Oscillator with divide-by-N with PLL module (FRCPLL) )
#pragma config PLLMODE = PLL4X          // PLL Mode Selection (4x PLL selected)
#pragma config IESO = ON                // Two-speed Oscillator Start-up Enable bit (Start up device with FRC, then switch to user-selected oscillator source)

// FOSC
#pragma config POSCMD = NONE            // Primary Oscillator Mode Select bits (Primary Oscillator disabled)
#pragma config OSCIOFCN = ON            // OSC2 Pin Function bit (OSC2 is general purpose digital I/O pin)
#pragma config SOSCSEL = OFF            // SOSC Power Selection Configuration bits (Digital (SCLKI) mode)
#pragma config PLLSS = PLL_FRC          // PLL Secondary Selection Configuration bit (PLL is fed by the on-chip Fast RC (FRC) oscillator)
#pragma config IOL1WAY = OFF            // Peripheral pin select configuration bit (Allow multiple reconfigurations)
#pragma config FCKSM = CSECMD           // Clock Switching Mode bits (Clock switching is enabled,Fail-safe Clock Monitor is disabled)

// FWDT
#pragma config WDTPS = PS32768          // Watchdog Timer Postscaler bits (1:32,768)
#pragma config FWPSA = PR128            // Watchdog Timer Prescaler bit (1:128)
#pragma config FWDTEN = OFF             // Watchdog Timer Enable bits (WDT and SWDTEN disabled)
#pragma config WINDIS = OFF             // Watchdog Timer Window Enable bit (Watchdog Timer in Non-Window mode)
#pragma config WDTWIN = WIN25           // Watchdog Timer Window Select bits (WDT Window is 25% of WDT period)
#pragma config WDTCMX = WDTCLK          // WDT MUX Source Select bits (WDT clock source is determined by the WDTCLK Configuration bits)
#pragma config WDTCLK = LPRC            // WDT Clock Source Select bits (WDT uses LPRC)

// FPOR
#pragma config BOREN = ON               // Brown Out Enable bit (Brown Out Enable Bit)
#pragma config LPCFG = OFF              // Low power regulator control (No Retention Sleep)
#pragma config DNVPEN = ENABLE          // Downside Voltage Protection Enable bit (Downside protection enabled using ZPBOR when BOR is inactive)

// FICD
#pragma config ICS = PGD2
#pragma config JTAGEN = OFF             // JTAG Enable bit (JTAG is disabled)
#pragma config BTSWP = OFF              // BOOTSWP Disable (BOOTSWP instruction disabled)

// FDEVOPT1
#pragma config ALTCMPI = DISABLE        // Alternate Comparator Input Enable bit (C1INC, C2INC, and C3INC are on their standard pin locations)
#pragma config TMPRPIN = OFF            // Tamper Pin Enable bit (TMPRN pin function is disabled)
#pragma config SOSCHP = ON              // SOSC High Power Enable bit (valid only when SOSCSEL = 1 (Enable SOSC high power mode (default))
#pragma config ALTVREF = ALTREFEN       // Alternate Voltage Reference Location Enable bit (VREF+ and CVREF+ on RA10, VREF- and CVREF- on RA9)



#include <xc.h>
#include <p24fxxxx.h>


#define FCY 32000000UL                  // Fosc in Hz; also, define this in lcd_func.c

#include "stdint.h"
#include "lcd.h"
#include "spi_drivers.h"
#include "libpic30.h"
#include "stdlib.h"
#include "timer.h"

#define NCS_SPI_FLASH       _LATG9
#define KEYB1               PORTDbits.RD6
#define KEYB2               PORTDbits.RD13
#define KEYB3               PORTAbits.RA7
#define KEYB4               PORTDbits.RD7

volatile uint32_t msec;

uint8_t fraction;
uint8_t mfg_id;
uint8_t dev_type;
uint8_t dev_id;


unsigned char block_protection_10[18]; /* global array to store block_protection data */
const char *teamName, *partName;
uint8_t busyMask;
uint32_t highestAddress;

struct device_profile {
    uint8_t mfg_id_el;
    unsigned int dev_type_el;
    unsigned int dev_id_el;
    char teamName_el[15];
    char partName_el[15];
    unsigned char busyMask_el;
    unsigned long highest_addr_el;
};

#define NUM_DEVICES 17

const struct device_profile flash_device[NUM_DEVICES] ={
    //{ mfg_id, dev_typ, dev_id,  teamName       ,  partName        , busyMask, highest_addr },  
    { 0xBF, 0x26, 0x02, "Microchip     ", "SST26VF032    ", 0x80, 0x03FFFFF}, //this device never reads the Status register right, it is always 0xFF, why? Likely because you can't erase in SPI mode, only SQI.
    { 0xBF, 0x25, 0x41, "Microchip     ", "SST25VF016B   ", 0x01, 0x01FFFFF},
    { 0xBF, 0x25, 0x4B, "Microchip     ", "SST25VF064C   ", 0x01, 0x07FFFFF},
    { 0xBF, 0x00, 0x00, "Microchip     ", "SST25VF032B   ", 0x01, 0x03FFFFF},
    { 0xBF, 0x26, 0x43, "Microchip     ", "SST26VF064B   ", 0x01, 0x07FFFFF},
    { 0xBF, 0x26, 0x42, "Microchip     ", "SST26VF032B   ", 0x01, 0x03FFFFF},
    { 0xBF, 0x26, 0x51, "Microchip     ", "SST26WF016B   ", 0x01, 0x01FFFFF},
    { 0xBF, 0x26, 0x41, "Microchip     ", "SST26VF016B   ", 0x01, 0x01FFFFF},
    { 0xBF, 0x26, 0x58, "Microchip     ", "SST26WF080B   ", 0x01, 0x00FFFFF},
    { 0xBF, 0x26, 0x54, "Microchip     ", "SST26WF040B   ", 0x01, 0x008FFFF},
    { 0xC2, 0x20, 0x17, "Macronix      ", "MX25L6445E    ", 0x01, 0x07FFFFF},
    { 0x20, 0x20, 0x16, "Micron        ", "M25P32-VMW6   ", 0x01, 0x03FFFFF},
    { 0xEF, 0x40, 0x17, "Winbond       ", "W25Q64FVAAI   ", 0x01, 0x07FFFFF},
    { 0x01, 0x40, 0x17, "Spansion      ", "S25FL164K     ", 0x01, 0x07FFFFF},
    { 0x7F, 0x9D, 0x46, "ISSI          ", "IS25CQ032     ", 0x01, 0x03FFFFF},
    { 0x1F, 0x46, 0x01, "Atmel         ", "AT26DF161A    ", 0x01, 0x01FFFFF},
    { 0x00, 0x00, 0x00, "None          ", "Empty         ", 0x01, 0x01FFFFF}
};

void Initialize(void);
void WriteEnable(void);
void ReadFlashID(void);
uint8_t ReadFlashStatus(void);
void ClearBlockProtectSST1();
void ClearBlockProtect(void);
void ChipErase(void);
void ResetOnKeyPress(void);
void TimerEventHandler(void);
void __attribute__((interrupt, auto_psv)) _T1Interrupt(void);
int main(void) {
    uint8_t i = 0;
    char b1, b2, b3, b4;

    Initialize();

    do {

        ReadFlashID();

        for (i = 0; i < NUM_DEVICES; i++) {
            if ((flash_device[i].mfg_id_el == mfg_id) && (flash_device[i].dev_type_el == dev_type) && (flash_device[i].dev_id_el == dev_id)) {
                teamName = flash_device[i].teamName_el;
                partName = flash_device[i].partName_el;
                busyMask = flash_device[i].busyMask_el;
            }
        }

        wrcmnd_lcd(SET_DDRAM + N2_ROW1);
        wrstr_lcd(partName);
        wrcmnd_lcd(SET_DDRAM + N2_ROW2);
        if (mfg_id == 0) {
            wrstr_lcd("Insert device  ");
        } else {
            wrstr_lcd("Press S4 key   ");
        }

        LATA = 0x01; // Indicates the erase was not done
    } while (teamName == flash_device[NUM_DEVICES - 1].teamName_el || KEYB2);
    // stay in loop until a device is plugged AND S4 is pressed 
    // <==> 
    // stay in loop while no device is plugged or S4 is read as "1"

    do {
        b1 = KEYB1;
        b2 = KEYB2; // S4
        b3 = KEYB3;
        b4 = KEYB4;
    }    while (b2); // Wait button to raise  

    ChipErase(); // Start erase procedure
    msec = 0; // Reset msec counter
    T1CONbits.TON = 1; // Start Timer1

    while ((ReadFlashStatus() & busyMask) == 1) {
        // writing to LCD takes at least 20 msec, so it is better to only do it once every [large random number]
        if ((msec > 0) && !(msec % 50)) {
            wrcmnd_lcd(SET_DDRAM + N2_ROW2);
            wrstr_lcd("Time: ");
            wrnr_lcd(msec);
            wrstr_lcd(" msec ");
        }
    };

    IEC0bits.T1IE = 0; // Disable Timer1 interrupts
    T1CONbits.TON = 0; // Stop timer; 

    wrcmnd_lcd(SET_DDRAM + N2_ROW1); // Display results on LCD
    wrstr_lcd("Chip erase     ");
    wrcmnd_lcd(SET_DDRAM + N2_ROW2);
    wrstr_lcd("Time: ");
    wrnr_lcd(msec);
    wrstr_lcd(" msec ");

    // Turn of LED on LATA and reset on any Key press
    LATA = 0x00; // Indicates the erase is completed
    ResetOnKeyPress();
    while (1) {
        //loop forever
    };

    return 0;
}

void Initialize(void) {
    PORTG = 0;
    PORTA = 0x0000;
    PORTD = 0x0000;
    LATA = 0x0000;
    LATD = 0x0000;
    TRISA = 0x0000;
    TRISD = 0x0000;
    TRISDbits.TRISD6 = 1;
    TRISDbits.TRISD13 = 1;
    TRISAbits.TRISA7 = 1;
    TRISDbits.TRISD7 = 1;

    spi1_init();

    // setup TIMER1    
    T1CON = 0x00; // Stops the Timer1 and reset control reg.
    TMR1 = 0x00; // Clear contents of the timer register
    PR1 = 0x3E80; // Period Register value match after 1 millisecond
    IPC0bits.T1IP = 0x01; // Setup Timer1 interrupt for desired priority level (This example assigns level 1 priority)
    IFS0bits.T1IF = 0; // Clear the Timer1 interrupt status flag
    IEC0bits.T1IE = 1; // Enable Timer1 interrupts
    T1CONbits.TCS = 0; // Timer1 Clock Source is Fosc / 2
    T1CONbits.TCKPS = 0; // Timer1 Prescale set to 1:1
    T1CONbits.TON = 0; // Start Timer1

    // initialize LCD    
    ini_lcd();
    clr_lcd();
    ini_lcd(); // ini_lcd is called twice to prevent black lines on LCD

    TIMER_SetConfiguration(TIMER_CONFIGURATION_1MS);
    TIMER_RequestTick(&TimerEventHandler, 1);
    T1CONbits.TON = 0;
    msec = 0;
}

void WriteEnable(void) {
    NCS_SPI_FLASH = 0;
    spi_wrbyte(0x06);
    NCS_SPI_FLASH = 1;
}

void ReadFlashID(void) {
    NCS_SPI_FLASH = 0;
    spi_wrbyte(0x9F);
    mfg_id = spi_rdbyte();
    dev_type = spi_rdbyte();
    dev_id = spi_rdbyte();
    NCS_SPI_FLASH = 1;
}

uint8_t ReadFlashStatus(void) {
    unsigned int flashStatus = 0x00;
    NCS_SPI_FLASH = 0;
    spi_wrbyte(0x05);
    flashStatus = spi_rdbyte();
    NCS_SPI_FLASH = 1;
    return flashStatus;
}

void ClearBlockProtectSST1(void) {
    uint8_t flashStatus1 = 0x00;

    // read status register first
    NCS_SPI_FLASH = 0;
    spi_wrbyte(0x05);
    flashStatus1 = spi_rdbyte();
    NCS_SPI_FLASH = 1;

    //modify flashstatus to clear protect bits
    flashStatus1 &= 0xC3;

    // write the new value to STATUS register
    NCS_SPI_FLASH = 0;
    spi_wrbyte(0x50);
    NCS_SPI_FLASH = 1; // ENABLE WRITE STATUS REGISTER
    NCS_SPI_FLASH = 0;
    spi_wrbyte(0x01);
    spi_wrbyte(flashStatus1);
    NCS_SPI_FLASH = 0;
}

void ClearBlockProtect(void) {
    unsigned char i = 0;
    if (dev_type == 0x25) {
        ClearBlockProtectSST1();
        return;
    }
    block_protection_10[0] = 0x00;
    block_protection_10[1] = 0x00;
    block_protection_10[2] = 0x00;
    block_protection_10[3] = 0x00;
    block_protection_10[4] = 0x00;
    block_protection_10[5] = 0x00;
    block_protection_10[6] = 0x00;
    block_protection_10[7] = 0x00;
    block_protection_10[8] = 0x00;
    block_protection_10[9] = 0x00;
    block_protection_10[10] = 0x00;
    block_protection_10[11] = 0x00;
    block_protection_10[12] = 0x00;
    block_protection_10[13] = 0x00;
    block_protection_10[14] = 0x00;
    block_protection_10[15] = 0x00;
    block_protection_10[16] = 0x00;
    block_protection_10[17] = 0x00;
    WriteEnable();
    NCS_SPI_FLASH = 0;
    spi_wrbyte(0x42);
    for (i = 18; i > 0; i--) spi_wrbyte(block_protection_10[i - 1]);
    NCS_SPI_FLASH = 1;

    //Florian's way for WINBOND
    if ((mfg_id == 0xEF) && (dev_type == 0x40) && (dev_id == 0x17)) {
        WriteEnable();
        NCS_SPI_FLASH = 0;
        spi_wrbyte(0x01);
        spi_wrbyte(0x00);
        NCS_SPI_FLASH = 1;
        while (ReadFlashStatus() & busyMask);
    }


}

void ChipErase(void) {
    ClearBlockProtect();
    WriteEnable();

    NCS_SPI_FLASH = 0;
    spi_wrbyte(0xC7);
    NCS_SPI_FLASH = 1;
}

void ResetOnKeyPress(void) {
    while (KEYB1 && KEYB2 && KEYB3 && KEYB4); // Wait a keyboard action(if not, loop) 
    __delay_ms(100); // Override keyboard hazard 
    while ((!KEYB1) || (!KEYB2) || (!KEYB3) || (!KEYB4)); // Wait end of action 
    exit(EXIT_SUCCESS); // Resets the CPU cleanly
}

void TimerEventHandler(void) {
    msec++;
}

void __attribute__((interrupt, auto_psv)) _T1Interrupt(void) {
    msec += 1; // Count milliseconds
    IFS0bits.T1IF = 0; // Reset Timer1 interrupt flag and Return from ISR
}