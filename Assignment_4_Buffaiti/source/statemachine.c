/*
 * statemachine.c
 *
 *  Created on: Oct 2, 2020
 *      Author: Arpit Savarkar / arpit.savarkar@colorado.edu
 */


#include "statemachine.h"
#include "switch.h"
#include "temp_systick.h"
#include "cap_sensor.h"
#include "led.h"

#ifdef DEBUG
	#define MSG_DEBUG PRINTF
#else // non-debug mode - get rid of printing message
	#define MSG_DEBUG(...)
#endif

/*************************************************************************************************
                                Global Flags
*************************************************************************************************/
volatile double val;
volatile int flag_250msec;
volatile int flag_750msec;
volatile int flag_Switch;


/*************************************************************************************************
                                Functions
*************************************************************************************************/

/* Structure for Handling */
struct traffic_light_t{
	color_t color_go;
	color_t color_stop;
	color_t color_warn;
	color_t color_crosswalk;
	state_t state;
	event_t event;
} traffic_light_t  = {
	.color_go.red   = ((HEX_GO >> 16) & 0xFF),
	.color_go.green = ((HEX_GO >> 8) & 0xFF),
	.color_go.blue  = (HEX_GO & 0xFF),
	.color_stop.red   = ((HEX_STOP >> 16) & 0xFF),
	.color_stop.green = ((HEX_STOP >> 8) & 0xFF),
	.color_stop.blue  = (HEX_STOP & 0xFF),
	.color_warn.red   = ((HEX_WARNING >> 16) & 0xFF),
	.color_warn.green = ((HEX_WARNING >> 8) & 0xFF),
	.color_warn.blue  = (HEX_WARNING & 0xFF),
	.color_crosswalk.red   = ((HEX_CROSSWALK >> 16) & 0xFF),
	.color_crosswalk.green = ((HEX_CROSSWALK >> 8) & 0xFF),
	.color_crosswalk.blue  = (HEX_CROSSWALK & 0xFF),
	.state       = s_STOP,
	.event       = e_Void,
};


/**
​ * ​ ​ @brief​ - Function to update event incase of succesfull Capacitive Touch​
​ *
​ * ​ ​ @param​ ​ goal:  (color_t) goal color to be set
 * ​ ​ @param​ ​ goal:  (event_t) event of the statemachine
​ * ​ ​ @return​ ​ (int) 1 if sucessfull touch , else 0
​ */
int cap_touch_action(color_t* goal, event_t* event) {
	int flag = 0;
	/* Sets flag if touch detected */
	flag = CAP_Scan();
	if(flag) {
		MSG_DEBUG("\n\r Capacitive Touch Detected at sec_time: %d", now()/1000 );
		/* Updates the goal color to CROSSWALK color state */
		*goal = traffic_light_t.color_crosswalk;
		/* Update event*/
		*event = e_TransitionTimeout;
		flag = 0;
		return 1;
	}
	return 0;
}


/**
​ * ​ ​ @brief​ - Function to update event incase of succesfull Button Press​
​ *
​ * ​ ​ @param​ ​ goal:  (color_t) goal color to be set
 * ​ ​ @param​ ​ goal:  (event_t) event of the statemachine
​ * ​ ​ @return​ ​ (int) 1 if sucessfull touch , else 0
​ */
int switch_action(color_t* goal, event_t* event) {

	if(flag_Switch) {
		MSG_DEBUG("\n\r Switch Button Detected at sec_time: %d", now()/1000 );
		/* Update goal color*/
		*goal = traffic_light_t.color_crosswalk;
		/* Update event*/
		*event = e_TransitionTimeout;
		PORTA->ISFR = 0xffffffff;
		flag_Switch = 0;
		return 1;
	}
	flag_Switch = 0;
	return 0;
}


/**
​ * ​ ​ @brief​ - Compares if two color sets are same​
​ *
​ * ​ ​ @param​ ​ color1:  (color_t) First color set
 * ​ ​ @param​ ​ goal:  (color_t) Second Color Set
​ * ​ ​ @return​ ​ (int) 1 if sucessfull touch , else 0
​ */
int compare_color(color_t color1, color_t color2) {

	return (color1.red == color2.red && color1.green == color2.green && color1.blue == color2.blue);
}


/**
​ * ​ ​ @brief​ - State Machine Function,
 * 				1) Updates the state and events in accordance to the Timeout for a Traffic Signal
 * 					with Cross walk.
 * 				2) Initializes the State with the Stop State​
​ *
​ * ​ ​ @param​ ​ none
​ * ​ ​ @return​ ​ none
​ */
void state_machine(void) {
	/* Intialzing start, goal, current color and new state
	 * These variables are used all over the state machine to keep track of state
	 * color - represets the current color set being lit up on the LED */
	state_t new_state = traffic_light_t.state;
	event_t event = traffic_light_t.event;
	color_t start = traffic_light_t.color_stop;
	color_t goal = traffic_light_t.color_go;
	color_t color = start;
	flag_Switch = 0;

	MSG_DEBUG("\n\r Initializing Traffic Signal Loop with State: STOP");

	// State Machine Infinite Loop Begin
	while(1) {
		switch(new_state) {
			// STOP state
			case s_STOP:
				// Resets the Timer before State Functionality
				reset_timer();
				flag_Switch = 0;
				MSG_DEBUG("\n\r Entering State 'STOP' at sec_time: %d", now()/1000 );
				start = traffic_light_t.color_stop; // Updates start color to - Stop Color Set
				goal = traffic_light_t.color_go; // Updates goal color to possible next state color
				color = traffic_light_t.color_stop; // Current Color to be seen on the LED
				LED_SET(color.red, color.green, color.blue); // Sets the Color
				new_state = s_TRANS; // Next State
				event = e_StopTimeout; // Current Event
				// Timeout Constraint
				// Exists the timeout incase of any touch (capacitive/button) with updated event
				while ((get_timer() < ROUTINE_TIMEOUT) && (event == e_StopTimeout)) {
					if(get_timer() % 100 == 0) {
						cap_touch_action(&goal, &event);
//						flag_Switch =0;
						switch_action(&goal, &event);
						}
					}
				break;

			// GO state
			case s_GO:
				// Resets the Timer before State Functionality
				reset_timer();
				flag_Switch = 0;
				MSG_DEBUG("\n\r Entering State 'GO' at sec_time: %d", now()/1000 );
				start = traffic_light_t.color_go; // Updates start color to - GO Color Set
				color = traffic_light_t.color_go; // Current Color to be seen on the LED
				LED_SET(color.red, color.green, color.blue); // Sets the Color
				new_state = s_TRANS; // Next State
				goal = traffic_light_t.color_warn;  // Updates goal color to possible next state color
				event = e_GoTimeout; // Current Event
				// Timeout Constraint
				// Exists the timeout incase of any touch (capacitive/button) with updated event
				while ((get_timer() < ROUTINE_TIMEOUT) && (event == e_GoTimeout)) {
					if(get_timer() % 100 == 0) {
						cap_touch_action(&goal, &event);
//						flag_Switch = 0;
						switch_action(&goal, &event);
						}
					}
				break;

			// WARNING state
			case s_WARNING:
				// Resets the Timer before State Functionality
				reset_timer();
				flag_Switch = 0;
				MSG_DEBUG("\n\r Entering State 'WARNING' at sec_time: %d", now()/1000 );
				start = traffic_light_t.color_warn; // Updates start color to - WARNING Color Set
				color = traffic_light_t.color_warn; // Current Color to be seen on the LED
				LED_SET(color.red, color.green, color.blue); // Sets the Color
				new_state = s_TRANS; // Next State
				goal = traffic_light_t.color_stop;  // Updates goal color to possible next state color
				event = e_WarnTimeout;  // Current Event
				// Timeout Constraint
				// Exists the timeout incase of any touch (capacitive/button) with updated event
				while ((get_timer() < WARN_TIMEOUT) && (event == e_WarnTimeout)) {
					if(get_timer() % 100 == 0) {
						cap_touch_action(&goal, &event);
//						flag_Switch = 0;
						switch_action(&goal, &event);
						}
					}
				break;

			// CROSSWALK state
			case s_CROSSWALK:
				// Resets the Timer before State Functionality
				reset_timer();
				new_state = s_TRANS; // Next State
				start = traffic_light_t.color_crosswalk; // Updates start color to - CROSSWALK Color Set
				color = traffic_light_t.color_crosswalk; // Current Color to be seen on the LED
				goal = traffic_light_t.color_go; // Updates goal color to possible next state color
				MSG_DEBUG("\n\r Entering State 'CROSSWALK' at sec_time: %d", now()/1000 );

				// Flashing CROSSWALK color state until 10 seconds
				while(get_timer() < CROSSWALK_TIMEOUT) {
					LED_SET(color.red, color.green, color.blue);
					Delay(750);
					LED_SET(0x00, 0x00, 0x00);
					Delay(250);
				}

//				LED_SET(color.red, color.green, color.blue);

				// Exists to GO_state color set .
				break;

			// TRANSITION state
			case s_TRANS:
				// Resets the Timer before State Functionality
				reset_timer();
				MSG_DEBUG("\n\r Smooth Transition Begins at sec_time: %d", now()/1000 );
				/* Following Functionality Updates the Color set to smoothly transition from the current color set
				 * Goal Color set, val is updated in the interrupt every 100 Hz
				 */
				val = 0;
				while( val <= 1 ) {
					color.blue = (goal.blue - start.blue) * (val) + start.blue ;  // Blue Color TPM updated
					color.red =  (goal.red - start.red) * (val) + start.red ; // Green Color TPM Updated
					color.green = (goal.green - start.green) * (val) + start.green ; // Green Color TPM Updated
					LED_SET(color.red, color.green, color.blue); // Sets the updated colors
					// Exit Condition Satisfied
					if (compare_color(color, goal)) {
						val = 0;
						break;
					}

				}

				/* The Following Conditional statements updates the next state depending on the exit color state post
				 * Transition Loop above
				 */
				// Setting Up the new state based on the color set
				// If current color set is same as GO state
				if(compare_color(color, traffic_light_t.color_go)) {
						new_state = s_GO;
						MSG_DEBUG("\n\r Smooth Transiton COMPLETE at sec_time: %d, onto State 'GO' ", now()/1000 );
					}
				// If current color set is same as STOP state
				else if(compare_color(color, traffic_light_t.color_stop)) {
					new_state = s_STOP;
					MSG_DEBUG("\n\r Smooth Transiton COMPLETE at sec_time: %d, onto State 'STOP' ", now()/1000 );
				}
				// If current color set is same as WARN state
				else if(compare_color(color, traffic_light_t.color_warn))  {
					new_state = s_WARNING;
					MSG_DEBUG("\n\r Smooth Transiton COMPLETE at sec_time: %d, onto State 'WARNING' ", now()/1000 );
				}
				// If current color set is same as CROSSWALK state
				else if(compare_color(color, traffic_light_t.color_crosswalk)) {
					new_state = s_CROSSWALK;
					MSG_DEBUG("\n\r Smooth Transiton COMPLETE at sec_time: %d, onto State 'CROSSWALK' ", now()/1000 );
				}

				break;
			// Failure Conditon
			default :
				MSG_DEBUG("\n\r State Unknown Failure Condition");
				break;

		}
	}

}
