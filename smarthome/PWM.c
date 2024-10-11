/*
 * PWM.c
 *
 *  Created on: Oct 4, 2024
 *      Author: Abdelrhman Adel Sakr
 */

#include "PWM.h"
#include"common_macros.h"
#include<avr/io.h>
#include"std_types.h"
#include"gpio.h"

void PWM_Timer0_Start(uint8 duty_cycle){
	GPIO_setupPinDirection(PORTB_ID,PIN3_ID,PIN_OUTPUT);
	CLEAR_BIT(TCCR0,FOC0);//this bit is set to zero in PWM
	SET_BIT(TCCR0,WGM01);//set the timer mode PWM
	SET_BIT(TCCR0,WGM00);
	SET_BIT(TCCR0,COM01);//Set OC0 to toggle each compare match and non inverting
	CLEAR_BIT(TCCR0,COM00);
	SET_BIT(TCCR0,CS02);//set the pre scaler to 1024
	SET_BIT(TCCR0,CS00);
	CLEAR_BIT(TCCR0,CS01);
	TCNT0=0;
	OCR0=(uint8)(((uint16)255*duty_cycle)/100);
//25% ---> OCR0=64
//50%--->OCR0=128
//75%--->OCR0=192
//100%---->OCR0=255
}
