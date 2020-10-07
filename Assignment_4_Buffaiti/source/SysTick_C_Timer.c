///*
// * SysTick_C_Timer.c
// *
// *  Created on: Oct 1, 2020
// *      Author: root
// */
//
//#include "led.h"
//#include "SysTick_C_Timer.h"
//#include "statemachine.h"
//#include "MKL25Z4.h"
//#include "stdio.h"
//
///**************************************************
//File Global (Static) Variables
//***************************************************/
//// Time tick counters
//volatile unsigned int trans_tick=0;
//
//
///**************************************************
//Global Variables - Initialized to 0
//***************************************************/
//
//
//void SysTick_Init(void) {
//	// Runs at 1000 Hz
//	SysTick->LOAD = (48000000L / 1000);
//	NVIC_SetPriority(SysTick_IRQn, 3);
//	SysTick->VAL = 0;
//	SysTick->CTRL = SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_CLKSOURCE_Msk ;
//	NVIC_ClearPendingIRQ(SysTick_IRQn);
//	NVIC_EnableIRQ(SysTick_IRQn);
//}
//
//void SysTick_E(void) {
//	NVIC_ClearPendingIRQ(SysTick_IRQn);
//	NVIC_EnableIRQ(SysTick_IRQn);
//}
//
//void SysTick_D(void) {
//	NVIC_ClearPendingIRQ(SysTick_IRQn);
//	NVIC_DisableIRQ(SysTick_IRQn);
//}
//
//
//void SysTick_Handler() {
//
//	trans_tick++;
//	if(trans_tick % 100 == 0){
//		val += 0.1;
//		if( val > 1) {
//			val = 1;
//		}
//	}
//
//	if(trans_tick == 250){
//		flag |= (1 << flag_250msec);
//	}
//
//	if(trans_tick == 750){
//		flag &= (~(1 << flag_250msec));
//		flag |= (1 << flag_750msec);
//	}
//
//	if(trans_tick == 1000){
//		flag &= (~(1 << flag_750msec));
//		flag |= (1 << flag_1000msec);
//		trans_secs++;
//	}
//
//	if(trans_secs == WARN_TIMEOUT){
//		flag |= (1 << flag_3000msec);
//	}
//
//	if(trans_secs == ROUTINE_TIMEOUT){
//		flag |= (1 << flag_TimeoutSec);
//		trans_tick = 0;
//	}
//
//}
