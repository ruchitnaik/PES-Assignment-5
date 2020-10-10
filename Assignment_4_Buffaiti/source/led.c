/*
 * pwm_led.c
 *
 *  Created on: Sep 30, 2020
 *      Author: Arpit Savarkar , arpit.savarkar
 */

#include "led.h"
#include "fsl_debug_console.h"


/**
​ * ​ ​ @brief​ ​ This function initializes the PWM Functionalities and TPM settings for PWM Control
 * 				and clock gating functionalities
​ *
​ * ​ ​ @param​ ​ PWM Levels - Described as a period
​ * ​ ​ @return​ ​ none
​ */
void Init_LED_PWM(uint16_t period) {

	// Enable Clock to PORTB and PORTD for (Red, Green) and Blue LED
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTD_MASK;
	SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK | SIM_SCGC6_TPM2_MASK;

	// Enable the FlexibleTImer configs that enable PWM capabilities
	// Red
	PORTB->PCR[RED_LED_PIN_POS] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[RED_LED_PIN_POS] |= PORT_PCR_MUX(3);

	// Green
	PORTB->PCR[GREEN_LED_PIN_POS] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[GREEN_LED_PIN_POS] |= PORT_PCR_MUX(3);

	//Blue
	PORTD->PCR[BLUE_LED_PIN_POS] &= ~PORT_PCR_MUX_MASK;
	PORTD->PCR[BLUE_LED_PIN_POS] |= PORT_PCR_MUX(4);

	// Configure TPM
	// Setting Clock Source at CPU rate - 48 Mhz
	SIM->SOPT2 |= (SIM_SOPT2_TPMSRC(1) | SIM_SOPT2_PLLFLLSEL_MASK);

	TPM0->MOD = period-1;
	TPM2->MOD = period-1;

	// Prescalar set to 1, no division
	TPM0->SC = TPM_SC_PS(0);
	TPM2->SC = TPM_SC_PS(0);

	// Contiunue Operation in Debug Mode
	TPM0->CONF |= TPM_CONF_DBGMODE(3);
	TPM2->CONF |= TPM_CONF_DBGMODE(3);

	// Channel Based Setup to Edge-alligned active-low PWM
	TPM2->CONTROLS[0].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK;
	TPM2->CONTROLS[1].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK;
	TPM0->CONTROLS[1].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK;

	// Setting Initial Duty cycle to 0
	TPM2->CONTROLS[0].CnV = 0;
	TPM2->CONTROLS[1].CnV = 0;
	TPM0->CONTROLS[1].CnV = 0;

	// Start TPM
	TPM2->SC |= TPM_SC_CMOD(1);
	TPM0->SC |= TPM_SC_CMOD(1);
#ifdef DEBUG
	PRINTF("\n\r Clock Gating and Initialization of TPM for PORTB and PORTD Complete ");
#endif
}


/**
​ * ​ ​ @brief​ ​ This function Sets the LED PWM converting from hex to PWM_PERIOD (0 - 48000)
​ *
​ * ​ ​ @param​ ​ red : Hex Value of RED Led
 * ​ ​ @param​ ​ green : Hex Value of GREEN Led
 * ​ ​ @param​ ​ blue : Hex Value of BLUE Led
​ * ​ ​ @return​ ​ none
​ */
void LED_SET(unsigned int red, unsigned int green,unsigned int blue) {

	BLUE_PWM = (blue * PWM_PERIOD) / 0xFF; // Blue
	RED_PWM = (red * PWM_PERIOD) / 0xFF; // Red
	GREEN_PWM = (green * PWM_PERIOD) / 0xFF; // Green

}
