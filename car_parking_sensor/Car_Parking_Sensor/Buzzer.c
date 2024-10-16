/*
 * Buzzer.c
 *
 *  Created on: Oct 5, 2024
 *      Author: Abdelrhman Adel Sakr
 */
#include "Buzzer.h"
#include "gpio.h"

void Buzzer_init(void){
	GPIO_setupPinDirection(BUZZER_PORT_ID,BUZZER_PIN_ID,PIN_OUTPUT);
}
void Buzzer_on(void){
	GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN_ID,LOGIC_HIGH);
}
void Buzzer_off(void){
	GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN_ID,LOGIC_LOW);
}
