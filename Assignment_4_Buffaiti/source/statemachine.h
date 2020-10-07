/*
 * statemachine.h
 *
 *  Created on: Oct 2, 2020
 *      Author: root
 */

#ifndef STATEMACHINE_H_
#define STATEMACHINE_H_

#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "stdint.h"
#include "stdbool.h"


/*************************************************************************************************
                                #define ' s
*************************************************************************************************/
#ifdef DEBUG
#define CROSSWALK_TIMEOUT 10
#define ROUTINE_TIMEOUT 5
#define WARN_TIMEOUT 3
#endif

#ifdef PRODUCTION
#define ROUTINE_TIMEOUT 20
#define WARN_TIMEOUT 5
#endif

#define MASK(x) (1UL << (x))

#define HEX_STOP 0x611E3C
#define HEX_GO 0x229622
#define HEX_WARNING 0xFFB200
#define HEX_CROSSWALK 0x001030


/*************************************************************************************************
                               Global Variables
*************************************************************************************************/
extern volatile double val;
extern volatile int flag_break;
extern volatile int flag_100msec;
extern volatile int flag_250msec;
extern volatile int flag_750msec;
extern volatile int flag_1000msec;
extern volatile int flag_3000msec;
extern volatile int flag_10000msec;
extern volatile int flag_TimeoutSec;
extern volatile int flag_Switch;
extern volatile uint8_t flag;



/*************************************************************************************************
                               Typededs
*************************************************************************************************/
typedef enum {

	s_STOP,
	s_GO,
	s_WARNING,
	s_CROSSWALK,
	s_TRANS
} state_t;

typedef enum {

	e_Void,
	e_Transition,
	e_Go,
	e_Stop,
	e_Warn,
	e_PollTouch
} event_t;

typedef struct color_t{
	int red;
	int green;
	int blue;
} color_t;

typedef struct traffic_signal_s traffic_signal_t;


/*************************************************************************************************
                                Function Prototypes
*************************************************************************************************/
void state_machine(void);


#endif /* STATEMACHINE_H_ */
