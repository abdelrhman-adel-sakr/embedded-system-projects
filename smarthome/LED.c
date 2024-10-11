/*
 * LED.c
 *
 *  Created on: Oct 4, 2024
 *      Author: Abdelrhman Adel Sakr
 */

#include "LED.h"
#include "std_types.h"
#include "gpio.h"
LED_ID Green = { .LED_PORT = PORTB_ID, .LED_PIN = PIN6_ID, ACTIVE_HIGH };
LED_ID Blue = { .LED_PORT = PORTB_ID, .LED_PIN = PIN7_ID, ACTIVE_HIGH };
LED_ID Red = { .LED_PORT = PORTB_ID, .LED_PIN = PIN5_ID, ACTIVE_HIGH };
void LEDS_init(LED_ID *id){
GPIO_setupPinDirection(id->LED_PORT,id->LED_PIN,PIN_OUTPUT);
LED_off(id);
}
void LED_on(LED_ID *id){
if(id->STATE==ACTIVE_LOW){
	GPIO_writePin(id->LED_PORT,id->LED_PIN,LOGIC_LOW);
}
else if(id->STATE==ACTIVE_HIGH){
	GPIO_writePin(id->LED_PORT,id->LED_PIN,LOGIC_HIGH);
}
}
void LED_off(LED_ID *id ){
	if(id->STATE==ACTIVE_LOW){
		GPIO_writePin(id->LED_PORT,id->LED_PIN,LOGIC_HIGH);
	}
	else if(id->STATE==ACTIVE_HIGH){
		GPIO_writePin(id->LED_PORT,id->LED_PIN,LOGIC_LOW);
	}
}
