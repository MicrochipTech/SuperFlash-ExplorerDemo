# SuperFlash® Chip Erase Timing Demo

![Hardware Photo](https://github.com/MicrochipTech/SuperFlash-ExplorerDemo/blob/05bcd506098254609ccc1250bb4667c536a98dee/docs/media/photo.jpg)

## Overview of Demo

Invented by Silicon Storage Technologies (SST) and later acquired by Microchip, SuperFlash® technology is an innovative flash memory technology providing erase times up to 1,000 times faster than competing flash memory technologies on the market. This demo illustrates this significant speed advantage by allowing the user to perform chip erase operations on serial flash memory devices while the board measures the erase time in real-time. (Flash memory devices feature multiple erase functions for various regions of memory. Chip erase was chosen for this demo as it requires the longest time, and therefore has the maximum impact.) The intent is to measure the timing of Microchip devices alongside various competitor devices so that the customer can see the difference first-hand. The table below lists the supported flash devices from Microchip and competitors. It includes the typical chip erase times measured on the devices to indicate the general range of timing to expect.

| Device | Density | Typical Chip Erase Time |
| :---- | :---: | :---: |
| [SST26VF064B](https://www.microchip.com/en-us/product/SST26VF064B) | 64 Mbit | 36ms |
| [SST26VF032B](https://www.microchip.com/en-us/product/SST26VF032B) | 32 Mbit | 38ms |
| [SST26WF016B](https://www.microchip.com/en-us/product/SST26WF016B) | 16 Mbit | 36ms |
| SSI IS25CQ032 | 32 Mbit | 13 seconds |
| Winbond W25Q64FV | 64 Mbit | 18 seconds | 
| Micron M25P32 | 32 Mbit | 35 seconds |
| Macronix MX25L6445E | 64 Mbit | 28 seconds| 
| Spansion S25FL164K | 64 Mbit | 46 seconds |

## List of Required Items

The following items are required to build the SuperFlash Chip Erase Timing Demo: 
1. Explorer 16/32 Development Kit with 100 pin PIC24FJ1024 PIM - [DM240001-3](https://www.microchip.com/en-us/development-tool/DM240001-3)
2. SQI SuperFlash Kit - [AC243009](https://www.microchip.com/en-us/development-tool/AC243009)

## Preparing the Demo 

Before the first use of the demo, the Explorer 16/32 board must be prepared. The demo uses the PIC24FJ1024GB610 PIM that comes with the Explorer 16/32 kit. This PIM must be programmed with the SuperFlash® Chip Erase Timing Demo firmware. 

Follow these steps to prepare the demo: 

1. Insert the PIC24FJ1024GB610 PIM onto the Explorer 16/32 
2. Connect the USB cable to the Explorer 16/32’s “PICkit on board” port 
3. Program the firmware using MPLAB X IDE 

## Running the Demo 

Follow these steps to run the demo: 

1. Remove USB cable from the Explorer 16/32 
2. Insert SuperFlash Click Board to test into mikroBUS A socket 
3. Connect the USB Cable 
4. Press push button S4 along bottom of board 
5. Wait for chip erase to complete (some competitors take a long time) 
6. Note the chip erase time reported by the board

> **Note:** Always remove power before changing Click Boards (do not hot-swap boards). If test stops at 0 ms or continues beyond 2 minutes, try resetting board by unplugging the USB cable.
