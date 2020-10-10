/*
 * switch.h
 *
 *  Created on: Oct 5, 2020
 *      Author: root
 */

#ifndef SWITCH_H_
#define SWITCH_H_

#include "MKL25Z4.h"
#include "statemachine.h"

/*************************************************************************************************
                                Macros
*************************************************************************************************/
#define SW1_SHIFT (5)	// on port A
#define SW1_POS (5)
#define MASK(x) (1UL << (x))
#define SWITCH_PRESSED(x) (!(PTD->PDIR & (MASK(x))))


/*************************************************************************************************
                             Function Prototypes
**************************************************************************************************/
/**
​ * ​ ​ @brief​ ​ This function initializes the Port A clock and MUX for GPIO
​ *
​ * ​ ​ @param​ ​ PWM Levels - Described as a period
​ * ​ ​ @return​ ​ none
​ */
void Init_Switch();


/**
​ * ​ ​ @brief​ ​ Interrupt Handler
​ *
​ * ​ ​ @param​ ​ none
​ * ​ ​ @return​ ​ none
​ */
void PORTA_IRQHandler(void);

#endif /* SWITCH_H_ */
