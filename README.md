# PES-Assignment-4
Author: Arpit Savarkar

## Repository Comments 
_Contains_
Code for Assignment 4 for Principals of Embedded Systems Software, ECEN-5813, Fall 2020
Kindly Consider the Flags which print the Debug Printf are only coded in the DEBUG and not in the Release mode(PRODUCTION Flag), incase of any discrepancy 
contact arpit.savarkar@colorado.edu

### Repository for PES-Assignment 1 

Source Code for this assignment can be found under source/ , Interrupts have been used for this Assignment 

- <b>Assignment_4_Buffaiti.c - The main script which demonstrates the start-up pattern and interaction between the slider and the LEDs on FRDM KL25Z </b>
- <b>led.h - Header file of led.c defining the led functions </b>
- <b>led.c - File containing LED Clock Gating Initialization and function which sets LED Color </b>
- <b>statemachine.h - Header file of statemachine.c defining State Machine Function Prototypes and Interrupts </b>
- <b>statemachine.c - File containing Statemachine functionalities implemented in accordance to Traffic Light State Machine </b>
- ![State Machine](../StateMachine.png) </b>
- <b>cap_sensor.h - Header file of delay.c defining functions to access and run the capacitive sensor </b>
- <b>cap_sensor.c - File containing definitions for clock gating and accessing the Capacitive Sensor </b>
- <b>switch.h - Header file of switch.c defining functions to access an external Push Button </b>
- <b>switch.c - File containing definitions for clock gating and accessing an External Push Button </b>
    - <b> PTA5 must be used to Connect the Switch Wiring, along with Necessary GROUND and POWER </b>
- <b>temp_systick.h - Header file of temp_systick.c defining functions to Instantiate </b>
- <b>switch.c - File containing definitions for clock gating and accessing an External Push Button </b>


## Project Comments
This projects implements the following routine : <br />
- At program startup, Blinkenlights will “test” the LED by blinking in the following pattern: <br />
    - When the traffic light is in the STOP state, Buffahiti residents use the color #611E3C  <br />
    - When the traffic light is in the GO state, Buffahiti residents use the color #229622 <br />
    - When the traffic light is in the WARNING state, Buffahiti residents use the color #FFB200 <br />
    - When someone presses the button to cross the street (CROSSWALK state), the traffic light is
        blinking with the color #001030. <br />
    - In the CROSSWALK state, the light blinks 250 msec off, 750 msec on. No other mode has the light
        blinking. <br />


## Installation/Execution Notes
Developed using MCUExpresso on Linux. <br />
Two configurations: <br />
    -D (Build Flags) <br />
    DEBUG Target - Prints DEBUG Messages to UART terminal. <br />
    Release Target - PRODUCTION Flag used, no debug messages are printed on UART Terminal <br />


## Extra Credit
Extra Credit Functionality to change state with using a button instead of Capactitive Touch Sensor is implemented
Both Capacitive Touch and Push Button Can be used 
    - <b> PTA5 must be used to Connect the Switch Wiring, along with Necessary GROUND and POWER </b>



