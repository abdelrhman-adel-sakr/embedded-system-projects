/*
 * DCmotor.c
 *
 *  Created on: Oct 4, 2024
 *      Author: Abdelrhman Adel Sakr
 */
#include "DCmotor.h"
#include "std_types.h"
#include "gpio.h"
#include "PWM.h"
DcMotor_ID fan = { .DC_MOTOR_PORT = PORTB_ID, .DC_MOTOR_PINA = PIN0_ID,
		.DC_MOTOR_PINB = PIN1_ID,.DC_MOTOR_PINE = PIN3_ID };
void DcMotor_init(DcMotor_ID *id ){
	GPIO_setupPinDirection(id->DC_MOTOR_PORT,id->DC_MOTOR_PINA,PIN_OUTPUT);
	GPIO_setupPinDirection(id->DC_MOTOR_PORT,id->DC_MOTOR_PINB,PIN_OUTPUT);
	GPIO_setupPinDirection(id->DC_MOTOR_PORT,id->DC_MOTOR_PINE,PIN_OUTPUT);
}
void DcMotor_Rotate(DcMotor_ID *motor,MOTOR_MODE state,uint8 speed){
	PWM_Timer0_Start(speed);
if(state==stop){
	GPIO_writePin(motor->DC_MOTOR_PORT,motor->DC_MOTOR_PINA,LOGIC_LOW);
	GPIO_writePin(motor->DC_MOTOR_PORT,motor->DC_MOTOR_PINB,LOGIC_LOW);
}
else if(state==Clockwise){
	GPIO_writePin(motor->DC_MOTOR_PORT,motor->DC_MOTOR_PINA,LOGIC_LOW);
	GPIO_writePin(motor->DC_MOTOR_PORT,motor->DC_MOTOR_PINB,LOGIC_HIGH);
}
else if(state==Anti_clockwise){
	GPIO_writePin(motor->DC_MOTOR_PORT,motor->DC_MOTOR_PINA,LOGIC_HIGH);
	GPIO_writePin(motor->DC_MOTOR_PORT,motor->DC_MOTOR_PINB,LOGIC_LOW);
}
}
