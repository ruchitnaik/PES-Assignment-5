/*
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 

/******************************************************************************
*​​Copyright​​ (C) ​​2020 ​​by ​​Arpit Savarkar
*​​Redistribution,​​ modification ​​or ​​use ​​of ​​this ​​software ​​in​​source​ ​or ​​binary
*​​forms​​ is​​ permitted​​ as​​ long​​ as​​ the​​ files​​ maintain​​ this​​ copyright.​​ Users​​ are
*​​permitted​​ to ​​modify ​​this ​​and ​​use ​​it ​​to ​​learn ​​about ​​the ​​field​​ of ​​embedded
*​​software. ​​Arpit Savarkar ​​and​ ​the ​​University ​​of ​​Colorado ​​are ​​not​ ​liable ​​for
*​​any ​​misuse ​​of ​​this ​​material.
*
******************************************************************************/
/**
 * @file Assignment_4_Buffaiti.c
 * @brief Application entry point.
 *
 * This file provides functions and abstractions for Initializing Systick, Capacitive Touch,
 * Switch and Calls State Machine Function
 *
 * @author Arpit Savarkar
 * @date September 10 2020
 * @version 1.0
 *
 *
  Sources of Reference :
  Textbooks : Embedded Systems Fundamentals with Arm Cortex-M based MicroControllers
  I would like to thank the SA's of the course Rakesh Kumar, Saket Penurkar and Howdy Pierece for their
  support to gain a deeper insight into State Machine Application
*/




#include <led.h>
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"

#include "temp_systick.h"
#include "statemachine.h"
#include "switch.h"
#include "cap_sensor.h"

/* TODO: insert other definitions and declarations here. */
/*
 * @brief   Application entry point.
 */
int main(void) {

  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
#endif
    /* Initializes Clock and related functionalities for SysTick */
    SysTick_Init();
    /* Initializes Clock and related functionalities for using Switch to transition between states */
    Init_Switch();
    /* Initializes Clock and related functionalities for using Capacitive Slider to transition between states */
    CAP_Init();
    /* Initializes Clock and related functionalities and TPM Setting s for using PORTB and PORTD under PWM settings to
     * operate the Red, Green and Blue LEDS's */
    Init_LED_PWM(PWM_PERIOD);
#ifdef DEBUG
	PRINTF("\n\r Entering Into the State Machine");
#endif
	// Enters into the State Machine Function
    state_machine();
    return 0 ;
}
