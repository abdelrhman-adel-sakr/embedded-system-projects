/*
 * LDR.h
 *
 *  Created on: Oct 4, 2024
 *      Author: Abdelrhman Adel Sakr
 */

#ifndef LDR_H_
#define LDR_H_
#include "std_types.h"
#define LDR_SENSOR_CHANNEL_ID 0
#define LDR_SENSOR_MAX_VOLT_VALUE 2.56
#define LDR_SENSOR_MAX_LIGHT_INTENSITY 100
extern uint8 LDR_sensor;
uint8 LDR_getLightIntensity(uint8 LDR_Channel1);
#endif /* LDR_H_ */
