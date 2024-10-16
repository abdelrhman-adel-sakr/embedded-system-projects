/*
 * Ultrasonic.h
 *
 *  Created on: Oct 11, 2024
 *      Author: Abdelrhman Adel Sakr
 */

#ifndef HAL_ULTRASONIC_ULTRASONIC_H_
#define HAL_ULTRASONIC_ULTRASONIC_H_

#include "std_types.h"

typedef struct {
	uint8 TRIGGER_PORT :2;
	uint8 TRIGGER_PIN :3;
	uint8 ECHO_PORT :2;
	uint8 ECHO_PIN :3;
} Ultrasonic_t;

extern Ultrasonic_t distance;

void Ultrasonic_init(Ultrasonic_t *Usonic);
void Ultrasonic_Trigger(Ultrasonic_t *Usonic);
uint16 Ultrasonic_readDistance(Ultrasonic_t *Usonic);
void Ultrasonic_edgeProcessing(void);

#endif /* HAL_ULTRASONIC_ULTRASONIC_H_ */
