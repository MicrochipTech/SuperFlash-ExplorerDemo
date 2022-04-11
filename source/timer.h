#include <xc.h>

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#ifndef TIMER_1MS
#define TIMER_1MS

#define TIMER_TICK_INTERVAL_MICRO_SECONDS 1000

/* Type Definitions ***********************************************/
typedef void (*TICK_HANDLER)(void);

typedef enum
{
    TIMER_CONFIGURATION_1MS,
    TIMER_CONFIGURATION_OFF
} TIMER_CONFIGURATIONS;

/*********************************************************************
* Function: void TIMER_CancelTick(TICK_HANDLER handle)
*
* Overview: Cancels a tick request.
*
* PreCondition: None
*
* Input:  handle - the function that was handling the tick request
*
* Output: None
*
********************************************************************/
void TIMER_CancelTick(TICK_HANDLER handle);

/*********************************************************************
* Function: bool TIMER_RequestTick(TICK_HANDLER handle, uint32_t rate)
*
* Overview: Requests to receive a periodic event.
*
* PreCondition: None
*
* Input:  handle - the function that will be called when the time event occurs
*         rate - the number of ticks per event.
*
* Output: bool - true if successful, false if unsuccessful
*
********************************************************************/
bool TIMER_RequestTick(TICK_HANDLER handle, uint32_t rate);

/*********************************************************************
* Function: bool TIMER_SetConfiguration(TIMER_CONFIGURATIONS configuration)
*
* Overview: Initializes the timer.
*
* PreCondition: TIMER_CONFIGURATIONS - configuration to run
*
* Input:  None
*
* Output: bool - true if successful, false if unsuccessful
*
********************************************************************/
bool TIMER_SetConfiguration(TIMER_CONFIGURATIONS configuration);

#endif //TIMER_1MS
