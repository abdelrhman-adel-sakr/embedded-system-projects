/*
 * flamesensor.h
 *
 *  Created on: Oct 5, 2024
 *      Author: Abdelrhma Adel Sakr
 */

#ifndef FLAMESENSOR_H_
#define FLAMESENSOR_H_
#include "std_types.h"
#define FLAMESENSOR_PORT PORTD_ID
#define FLAMESENSOR_PIN PIN2_ID

void FlameSensor_init(void);
uint8 FlameSensor_getValue(void);
#endif /* FLAMESENSOR_H_ */
