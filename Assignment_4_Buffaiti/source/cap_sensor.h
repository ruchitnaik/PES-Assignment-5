/*
 * cap_sensor.h
 *
 *  Created on: Oct 3, 2020
 *      Author: root
 */

#ifndef CAP_SENSOR_H_
#define CAP_SENSOR_H_


#include "MKL25Z4.h"
#include "statemachine.h"
#include "stdint.h"
#include "stdio.h"
#include "fsl_debug_console.h"

/* ************************************************************************
 * Macros
 **************************************************************************/
#define SCAN_OFFSET 588  // Offset for scan range
#define SCAN_DATA TSI0->DATA & 0xFFFF // Accessing the bits held in TSI0_DATA_TSICNT
#define NOISE_LOW 25
#define NOISE_HIGH 60000

/* ************************************************************************
 * Prototypes
 **************************************************************************/

/* ​ ​ @brief​ ​ Initialization of Capacitive Sensor (Clocks Gating etc) */
void CAP_Init(void);


/**
​ * ​ ​ @brief​ ​ Helper Function to return back the Value sensed by the capacitive sensor
​ *
 *
​ * ​ ​ @param​ ​ void
​ *
​ * ​ ​ @return​ ​ Boolean if Touch within threshold
​ */
uint16_t CAP_Scan(void);


#endif /* CAP_SENSOR_H_ */
