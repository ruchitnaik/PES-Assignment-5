/*
 * pwm_led.h
 *
 *  Created on: Sep 30, 2020
 *      Author: root
 */

#ifndef LED_H_
#define LED_H_

#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include <stdbool.h>
#include <stdio.h>


/*************************************************************************************************
                                #define ' s
*************************************************************************************************/
#define PWM_PERIOD (48000)

#define BLUE_PWM TPM0->CONTROLS[1].CnV
#define RED_PWM TPM2->CONTROLS[0].CnV
#define GREEN_PWM TPM2->CONTROLS[1].CnV

#define RED_LED_PIN_POS (18)
#define GREEN_LED_PIN_POS (19)
#define BLUE_LED_PIN_POS (1)


/*************************************************************************************************
                             Functions
**************************************************************************************************/

/**
​ * ​ ​ @brief​ ​ This function initializes the PWM Functionalities and TPM settings for PWM Control
 * 				and clock gating functionalities
​ *
​ * ​ ​ @param​ ​ PWM Levels - Described as a period
​ * ​ ​ @return​ ​ none
​ */
void Init_LED_PWM(uint16_t period);


/**
​ * ​ ​ @brief​ ​ This function Sets the LED PWM converting from hex to PWM_PERIOD (0 - 48000)
​ *
​ * ​ ​ @param​ ​ red : Hex Value of RED Led
 * ​ ​ @param​ ​ green : Hex Value of GREEN Led
 * ​ ​ @param​ ​ blue : Hex Value of BLUE Led
​ * ​ ​ @return​ ​ none
​ */
void LED_SET(unsigned int red, unsigned int green, unsigned int blue);

#endif /* LED_H_ */
