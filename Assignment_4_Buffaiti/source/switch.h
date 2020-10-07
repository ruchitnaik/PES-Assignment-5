/*
 * switch.h
 *
 *  Created on: Oct 5, 2020
 *      Author: root
 */

#ifndef SWITCH_H_
#define SWITCH_H_

#include "MKL25Z4.h"

#define SW1_SHIFT (5)	// on port A
#define SW1_POS (5)
#define MASK(x) (1UL << (x))
#define SWITCH_PRESSED(x) (!(PTD->PDIR & (MASK(x))))

void Init_Switch();
void PORTA_IRQHandler(void);

#endif /* SWITCH_H_ */
