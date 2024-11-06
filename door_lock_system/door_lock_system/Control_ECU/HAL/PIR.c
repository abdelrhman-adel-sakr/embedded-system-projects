/*
 * PIR.c
 *
 *  Created on: Oct 25, 2024
 *      Author: Abdelrhman Adel Sakr
 */
#include "PIR.h"
#include <avr/io.h>
#include "../MCAL/gpio.h"
PIR_ConfigType pir_config={.PIR_PORT=PORTC_ID,.PIR_PIN=PIN2_ID};
void PIR_init(const PIR_ConfigType *config) {
    // Set PIR_SENSOR_PIN as input
	GPIO_setupPinDirection(config->PIR_PORT,config->PIR_PIN,PIN_INPUT);
}

uint8_t PIR_getState(void) {
    // Return the state of the PIR sensor (0: no motion, 1: motion detected)
    return GPIO_readPin(pir_config.PIR_PORT, pir_config.PIR_PIN);
}
