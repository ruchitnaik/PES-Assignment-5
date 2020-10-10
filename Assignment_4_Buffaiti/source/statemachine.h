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
                                MACROS
*************************************************************************************************/
#ifdef DEBUG
#define CROSSWALK_TIMEOUT 10000
#define ROUTINE_TIMEOUT 5000
#define WARN_TIMEOUT 3000
#endif

#ifdef PRODUCTION
#define CROSSWALK_TIMEOUT 10000
#define ROUTINE_TIMEOUT 20000
#define WARN_TIMEOUT 5000
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
extern volatile int flag_250msec;
extern volatile int flag_750msec;
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
	e_TransitionTimeout,
	e_GoTimeout,
	e_StopTimeout,
	e_WarnTimeout
} event_t;

typedef struct color_t{
	int red;
	int green;
	int blue;
} color_t;


/*************************************************************************************************
                                Function Prototypes
*************************************************************************************************/
void state_machine(void);


/**
​ * ​ ​ @brief​ - Function to update event incase of succesfull Capacitive Touch​
​ *
​ * ​ ​ @param​ ​ goal:  (color_t) goal color to be set
 * ​ ​ @param​ ​ goal:  (event_t) event of the statemachine
​ * ​ ​ @return​ ​ (int) 1 if sucessfull touch , else 0
​ */
int cap_touch_action(color_t* goal, event_t* event);


/**
​ * ​ ​ @brief​ - Function to update event incase of succesfull Button Press​
​ *
​ * ​ ​ @param​ ​ goal:  (color_t) goal color to be set
 * ​ ​ @param​ ​ goal:  (event_t) event of the statemachine
​ * ​ ​ @return​ ​ (int) 1 if sucessfull touch , else 0
​ */
int switch_action(color_t* goal, event_t* event);


/**
​ * ​ ​ @brief​ - Compares if two color sets are same​
​ *
​ * ​ ​ @param​ ​ color1:  (color_t) First color set
 * ​ ​ @param​ ​ goal:  (color_t) Second Color Set
​ * ​ ​ @return​ ​ (int) 1 if sucessfull touch , else 0
​ */
int compare_color(color_t color1, color_t color2);
#endif /* STATEMACHINE_H_ */
