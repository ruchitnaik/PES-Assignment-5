/*
 * switch.c
 *
 *  Created on: Oct 5, 2020
 *      Author: root
 */

#include "switch.h"
#include "statemachine.h"


/**
​ * ​ ​ @brief​ ​ This function initializes the Port A clock and MUX for GPIO
​ *
​ * ​ ​ @param​ ​ PWM Levels - Described as a period
​ * ​ ​ @return​ ​ none
​ */
void Init_Switch() {


	// SWITCH CAPABILITIES Initialization
	// Push Button Switch
	// Select port A on pin mux, enable pull-up resistors
	PORTA->PCR[SW1_POS] = PORT_PCR_MUX(1) | PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_IRQC(11);
	// Clear switch bits to input
	PTA->PDDR &= ~MASK(SW1_POS);
	// Enabling Interrupts
	/* Configure NVIC */
	NVIC_SetPriority(PORTA_IRQn, 3);
	NVIC_ClearPendingIRQ(PORTA_IRQn);
	NVIC_EnableIRQ(PORTA_IRQn);

	/* Configure PRIMASK */
	__enable_irq();

}


/**
​ * ​ ​ @brief​ ​ Interrupt Controller for PORT A
​ *
​ * ​ ​ @param​ ​ none
​ * ​ ​ @return​ ​ none
​ */
void PORTA_IRQHandler(void) {

	flag_Switch = 0;

	// ISFR success
	if ((PORTA->ISFR & MASK(SW1_POS))) {
		flag_Switch = 0;
			if (SWITCH_PRESSED(SW1_POS)) { // crosswalk state matched
				flag_Switch = 1;
			}
		}
	// clear status flags
	PORTA->ISFR = 0xffffffff;
}

