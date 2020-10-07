/*
 * statemachine.c
 *
 *  Created on: Oct 2, 2020
 *      Author: root
 */


#include "statemachine.h"
#include "switch.h"
#include "temp_systick.h"
#include "cap_sensor.h"
#include "led.h"

/*************************************************************************************************
                                Global Flags
*************************************************************************************************/
volatile double val;
volatile int flag_break;
volatile int flag_10msec;
volatile int flag_100msec;
volatile int flag_250msec;
volatile int flag_750msec;
volatile int flag_1000msec;
volatile int flag_3000msec;
volatile int flag_10000msec;
volatile int flag_TimeoutSec;
volatile int flag_Switch;

struct traffic_light_t{
	color_t color_go;
	color_t color_stop;
	color_t color_warn;
	color_t color_crosswalk;
	state_t state;
	event_t event;
	uint32_t Timeout;
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
	.Timeout     = ROUTINE_TIMEOUT
};


void state_machine(void) {
	state_t new_state = traffic_light_t.state;
	color_t start = traffic_light_t.color_stop;
	color_t goal = traffic_light_t.color_go;

	int flag = 0;
	color_t color = start;

#ifdef DEBUG_
	PRINTF("Initializing Traffic Signal State with State: STOP");
#endif

	while(1) {
		switch(new_state) {

			case s_STOP:
//				reset_timer();
				start = traffic_light_t.color_stop;
				color = traffic_light_t.color_stop;
				LED_SET(color.red, color.green, color.blue);

				// Timeout Satisfied
				if(flag_TimeoutSec == 1) {
					new_state = s_TRANS;
					goal = traffic_light_t.color_go;
					flag_TimeoutSec = 0;
					break;
				}
//				flag_Switch = 0;
				if ( flag_TimeoutSec != 1 ) {
					// Checks For a Switch
						if(flag_Switch) {

							new_state = s_TRANS;
							goal = traffic_light_t.color_crosswalk;
							flag_Switch = 0;
							break;
						}
					flag_Switch = 0;
				}

				if ( flag_TimeoutSec != 1 ) {
					flag = 0;
					// Checks For a Capacitive Touch
					if( flag_100msec == 1 ) {
						flag = CAP_Scan();
						if(flag) {
							new_state = s_TRANS;
							goal = traffic_light_t.color_crosswalk;
							flag_100msec = 0;
							flag = 0;
							break;
						}
					flag_100msec = 0;
					}

				}
				break;

			case s_GO:
//				reset_timer();
				start = traffic_light_t.color_go;
				color = traffic_light_t.color_go;
				LED_SET(color.red, color.green, color.blue);

				// Timeout Satisfied
				if(flag_TimeoutSec == 1) {
					new_state = s_TRANS;
					goal = traffic_light_t.color_warn;
					flag_TimeoutSec = 0;
					break;
				}

				if ( flag_TimeoutSec != 1 ) {
					// Checks For a Switch
						if(flag_Switch) {
							new_state = s_TRANS;
							goal = traffic_light_t.color_crosswalk;
							flag_100msec = 0;
							flag_Switch = 0;
							break;
						}
					PORTA->ISFR = 0xffffffff;
					flag_Switch = 0;
				}

				if ( flag_TimeoutSec != 1 ) {
					flag = 0;
					// Checks For a Capacitive Touch
					if( flag_100msec == 1 ) {
						flag = CAP_Scan();
						if(flag) {
							new_state = s_TRANS;
							goal = traffic_light_t.color_crosswalk;
							flag_100msec = 0;
							flag = 0;
							break;
						}
					flag_100msec = 0;
					}

				}

				break;


			case s_WARNING:
//				reset_timer();
				start = traffic_light_t.color_warn;
				color = traffic_light_t.color_warn;
				LED_SET(color.red, color.green, color.blue);

				// Timeout Satisfied
				if(flag_3000msec == 1) {
					new_state = s_TRANS;
					goal = traffic_light_t.color_stop;
					flag_TimeoutSec = 0;
					break;
				}


				if ( flag_TimeoutSec != 1 ) {
					// Checks For a Switch
						if(flag_Switch) {
							new_state = s_TRANS;
							goal = traffic_light_t.color_crosswalk;
							flag_100msec = 0;
							flag_Switch = 0;
							break;
						}
					flag_Switch = 0;
				}

				if ( flag_3000msec != 1 ) {
					flag = 0;
					// Checks For a Capacitive Touch
					if( flag_100msec == 1 ) {
						flag = CAP_Scan();
						if(flag) {
							new_state = s_TRANS;
							goal = traffic_light_t.color_crosswalk;
							flag_100msec = 0;
							flag = 0;
							break;
						}
					flag_100msec = 0;
					}

				}
				break;


			case s_CROSSWALK:

				start = traffic_light_t.color_crosswalk;
				color = traffic_light_t.color_crosswalk;

				while(flag_10000msec != 1) {
					if ( flag_750msec == 1 ) {
						LED_SET(0x00, 0x00, 0x00);
						}
					else {
						LED_SET(color.red, color.green, color.blue);
					}
				}
				flag_10000msec = 0;
				LED_SET(color.red, color.green, color.blue);
				new_state = s_TRANS;
				goal = traffic_light_t.color_go;
//				reset_timer();
				break;



			case s_TRANS:
				if(color.green == goal.green && color.red == goal.red && color.blue == goal.blue){
					goto next;
				}

				val = 0;
				while( val <= 1 ) {
					if(color.green == goal.green && color.red == goal.red && color.blue == goal.blue){
						val = 0;
						goto next;
					}
					color.blue = (goal.blue - start.blue) * (val) + start.blue ;
					color.red =  (goal.red - start.red) * (val) + start.red ;
					color.green = (goal.green - start.green) * (val) + start.green ;
					LED_SET(color.red, color.green, color.blue);
					if(color.green == goal.green && color.red == goal.red && color.blue == goal.blue){
						val = 0;
						goto next;
					}

				}
				// Setting Up the new state based on the color set
				next:
					if(new_state == s_CROSSWALK) {
						new_state = s_GO;
					}
					if(color.red == traffic_light_t.color_go.red && color.green == traffic_light_t.color_go.green && color.blue == traffic_light_t.color_go.blue) {
						new_state = s_GO;
					}
					else if(color.red == traffic_light_t.color_stop.red && color.green == traffic_light_t.color_stop.green && color.blue == traffic_light_t.color_stop.blue) {
						new_state = s_STOP;
					}
					else if(color.red == traffic_light_t.color_warn.red && color.green == traffic_light_t.color_warn.green && color.blue == traffic_light_t.color_warn.blue)  {
						new_state = s_WARNING;
					}
					else if(color.red == traffic_light_t.color_crosswalk.red && color.green == traffic_light_t.color_crosswalk.green && color.blue == traffic_light_t.color_crosswalk.blue) {
						new_state = s_CROSSWALK;
					}
					LED_SET(0x00, 0x00, 0x00);
					reset_timer();
				break;

		}

	}
}
