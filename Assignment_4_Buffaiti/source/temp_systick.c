/*
 * temp_systick.c
 *
 *  Created on: Oct 3, 2020
 *      Author: root
 */

#include "temp_systick.h"


/*************************************************************************************************
                                Global Variables
*************************************************************************************************/
volatile ticktime_t trans_tick;
volatile ticktime_t trans_secs;
volatile ticktime_t Timer_U32;

volatile ticktime_t g_program_start;
volatile ticktime_t g_timer_start;

/*************************************************************************************************
                                Functions
*************************************************************************************************/


/**
​ * ​ ​ @brief​ ​ This function initializes the systick timer with 1ms tick time.
 *              1ms timer value for 100Mhz clock.
 *              COUNT_PER_MS = 48Mhz / 1000(ticks/sec) - 1 = 48000000/1000 - 1 = 47999;
​ *
​ * ​ ​ @param​ ​ none
​ * ​ ​ @return​ ​ none
​ */
void SysTick_Init(void) {

	SysTick->LOAD = (COUNT_PER_MS);  // 1000 Hz
	NVIC_SetPriority(SysTick_IRQn, 3); // NVIC Interrupt Priority // 3
	NVIC_ClearPendingIRQ(SysTick_IRQn); // Clear Pending IRq's
	NVIC_EnableIRQ(SysTick_IRQn);
	SysTick->VAL = 0; // Clear Timer
	SysTick->CTRL = SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_CLKSOURCE_Msk ;  // Mask to Initialize TIcks, Enamble CTRL Mask and use Processer CLock Source of 48 Mhz

	trans_tick = 0; // Extra Precaution during Initialization
	Timer_U32 = 0; // Overall CLock - Initialization Precauton
	g_program_start = g_timer_start = 0;
#ifdef DEBUG
	PRINTF("\n\r Clock Gating and Initialization of SysTick Complete ");
#endif

}


/**
​ * ​ ​ @brief​ ​  This functions returns the time in ms since the power on.
                Max time=0xffffffff ms after that it rolls back to 0.
​ *
​ * ​ ​ @param​ ​ none
​ * ​ ​ @return​ ​ none
​ */
ticktime_t now() {
	return Timer_U32 - g_program_start;
}


/**
​ * ​ ​ @brief​ ​ Resets the Flags and Trans_tick to DEFAULT(0)
​ *
​ * ​ ​ @param​ ​ none
​ * ​ ​ @return​ ​ none
​ */
void reset_timer() {
	g_timer_start = Timer_U32;
}


/**
​ * ​ ​ @brief​ ​ Returns the number of ticks from reset
​ *
​ * ​ ​ @param​ ​ none
​ * ​ ​ @return​ ​ Integer - Number of Ticks
​ */
ticktime_t get_timer() {

	return (Timer_U32 - g_timer_start);
}


/**
​ * ​ ​ @brief​ ​ Interrupt Handler Function. A counter will be incremented to keep track of Ms.
 *           Handles Smooth Trasition increments and Flags
​ *
​ * ​ ​ @param​ ​ none
​ * ​ ​ @return​ ​ none
​ */
void SysTick_Handler(){

	Timer_U32++; // Keep Track of the total timer

	/* A functionality which helps for smooth transition,
	 * I found this gave me the smoothest transition
	 */
	if(Timer_U32 % 100 == 0){
		val += 0.1;
		if(val > 1) {
			val = 1;
		}
	}

	/* Functionality which is used to check Blinking required Crosswalk state */
	if(Timer_U32 % 250 == 0){
		flag_750msec = 0;
		flag_250msec = 1;
	}

	if(Timer_U32 % 750  == 0){
		flag_250msec = 0;
		flag_750msec = 1;
	}
}




