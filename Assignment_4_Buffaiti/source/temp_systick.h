/*
 * temp_systick.h
 *
 *  Created on: Oct 3, 2020
 *      Author: root
 */

#ifndef TEMP_SYSTICK_H_
#define TEMP_SYSTICK_H_

#include "MKL25Z4.h"
#include "stdio.h"
#include "stdint.h"
#include "stdbool.h"
#include "statemachine.h"

/*************************************************************************************************
                             #typedef's
**************************************************************************************************/
typedef uint32_t ticktime_t; // Stores in the resolution of 1000 Hz


/*************************************************************************************************
                             Macros
**************************************************************************************************/
/* 48Mhz / 1000 Hz -1 47999 that runs at 1ms */
#define COUNT_PER_MS 47999


/*************************************************************************************************
                             Global Variables
**************************************************************************************************/
extern volatile ticktime_t trans_tick;
extern volatile ticktime_t Timer_U32;


/*************************************************************************************************
                                Function Prototypes
*************************************************************************************************/

/**
​ * ​ ​ @brief​ ​ This function initializes the systick timer with 1ms tick time.
 *              1ms timer value for 100Mhz clock.
 *              COUNT_PER_MS = 48Mhz / 1000(ticks/sec) - 1 = 48000000/1000 - 1 = 47999;
​ *
​ * ​ ​ @param​ ​ none
​ * ​ ​ @return​ ​ none
​ */
void SysTick_Init(void);

/**
​ * ​ ​ @brief​ ​ Interrupt Handler Function. A counter will be incremented to keep track of Ms.
 *           Handles Smooth Trasition increments and Flags
​ *
​ * ​ ​ @param​ ​ none
​ * ​ ​ @return​ ​ none
​ */
void SysTick_Handler();

//
//void SysTick_E(void);   // Enables the Systick Functionalities
//void SysTick_D(void);	// Disables the Functionalities


/**
​ * ​ ​ @brief​ ​  This functions returns the time in ms since the power on.
                Max time=0xffffffff ms after that it rolls back to 0.
​ *
​ * ​ ​ @param​ ​ none
​ * ​ ​ @return​ ​ none
​ */
ticktime_t now(); // returns time since startup


/**
​ * ​ ​ @brief​ ​ Resets the Flags and Trans_tick to DEFAULT(0)
 *           Doesn't affect now() values
​ *
​ * ​ ​ @param​ ​ none
​ * ​ ​ @return​ ​ none
​ */
void reset_timer();


/**
​ * ​ ​ @brief​ ​ Returns the number of ticks from reset
​ *
​ * ​ ​ @param​ ​ none
​ * ​ ​ @return​ ​ Integer - Number of Ticks
​ */
ticktime_t get_timer();


/**
​ * ​ ​ @brief​ ​ Delays for a particular period of time
​ *
​ * ​ ​ @param​ ​ none
​ * ​ ​ @return​ ​ Integer - Number of Ticks
​ */
void Delay (uint32_t Ticks);

#endif /* TEMP_SYSTICK_H_ */
