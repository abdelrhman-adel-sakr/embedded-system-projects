/*
 * Ultrasonic.c
 *
 *  Created on: Oct 11, 2024
 *      Author: Abdelrhman Adel Sakr
 */

#include "Ultrasonic.h"
#include "gpio.h"
#include "icu.h"
#include "util/delay.h"

ICU_ClockType ICU_config = { F_CPU_8, RAISING };
uint8 edge_count = 0;
uint32 time_high = 0;

Ultrasonic_t distance = { .TRIGGER_PORT = PORTD_ID, .TRIGGER_PIN =
PIN7_ID, .ECHO_PORT = PORTD_ID, .ECHO_PIN = PIN6_ID };

void Ultrasonic_init(Ultrasonic_t *Usonic) {
	ICU_init(&ICU_config);
	ICU_setCallBack(Ultrasonic_edgeProcessing);
	GPIO_setupPinDirection(Usonic->TRIGGER_PORT, Usonic->TRIGGER_PIN,
			PIN_OUTPUT);
}
void Ultrasonic_Trigger(Ultrasonic_t *Usonic) {
	GPIO_writePin(Usonic->TRIGGER_PORT, Usonic->TRIGGER_PIN, LOGIC_HIGH);
	_delay_us(10);
	GPIO_writePin(Usonic->TRIGGER_PORT, Usonic->TRIGGER_PIN, LOGIC_LOW);
}
uint16 Ultrasonic_readDistance(Ultrasonic_t *Usonic) {
	Ultrasonic_Trigger(Usonic);
	if (edge_count == 2) {
		edge_count = 0;
		return ((time_high + 100) * 0.0085);
	}
}
void Ultrasonic_edgeProcessing(void) {
	edge_count++;
	if (edge_count == 1) {
		ICU_clearTimerValue();
		ICU_setEdgeDetectionType(FALLING);
	} else if (edge_count == 2) {
		time_high = ICU_getInputCaptureValue();
		ICU_setEdgeDetectionType(RAISING);
	}
}
