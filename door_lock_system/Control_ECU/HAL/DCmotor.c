/*
 * DCmotor.c
 *
 *  Created on: Oct 4, 2024
 *      Author: Abdelrhman Adel Sakr
 */
#include "DCmotor.h"
#include "../MCAL/gpio.h"
#include "../MCAL/PWM.h"
DcMotor_ID Door = { .DC_MOTOR_PORT = PORTD_ID, .DC_MOTOR_PINA = PIN6_ID,
		.DC_MOTOR_PINB = PIN7_ID,.DC_MOTOR_PORT_EN=PORTB_ID,.DC_MOTOR_PINE = PIN3_ID };
void DcMotor_init(DcMotor_ID *id ){
	GPIO_setupPinDirection(id->DC_MOTOR_PORT,id->DC_MOTOR_PINA,PIN_OUTPUT);
	GPIO_setupPinDirection(id->DC_MOTOR_PORT,id->DC_MOTOR_PINB,PIN_OUTPUT);
	GPIO_setupPinDirection(id->DC_MOTOR_PORT_EN,id->DC_MOTOR_PINE,PIN_OUTPUT);
}
void DcMotor_Rotate(DcMotor_ID *motor,MOTOR_MODE state,uint8 speed){
	PWM_Timer0_Start(speed);
if(state==stop){
	GPIO_writePin(motor->DC_MOTOR_PORT,motor->DC_MOTOR_PINA,LOGIC_LOW);
	GPIO_writePin(motor->DC_MOTOR_PORT,motor->DC_MOTOR_PINB,LOGIC_LOW);
}
else if(state==Clockwise){
	GPIO_writePin(motor->DC_MOTOR_PORT,motor->DC_MOTOR_PINA,LOGIC_HIGH);
	GPIO_writePin(motor->DC_MOTOR_PORT,motor->DC_MOTOR_PINB,LOGIC_LOW);
}
else if(state==Anti_clockwise){
	GPIO_writePin(motor->DC_MOTOR_PORT,motor->DC_MOTOR_PINA,LOGIC_LOW);
	GPIO_writePin(motor->DC_MOTOR_PORT,motor->DC_MOTOR_PINB,LOGIC_HIGH);
}
}
