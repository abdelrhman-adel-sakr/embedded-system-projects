/*
 * flamesensor.c
 *
 *  Created on: Oct 5, 2024
 *      Author: Abdelrhman Adel Sakr
 */
#include "flamesensor.h"
#include "gpio.h"
void FlameSensor_init(void){
	GPIO_setupPinDirection(FLAMESENSOR_PORT,FLAMESENSOR_PIN,PIN_OUTPUT);
}
uint8 FlameSensor_getValue(void){
return GPIO_readPin(FLAMESENSOR_PORT,FLAMESENSOR_PIN);
}
