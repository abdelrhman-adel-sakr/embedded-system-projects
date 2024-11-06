/*
 * DCmotor.h
 *
 *  Created on: Oct 4, 2024
 *      Author: Abdelrhman Adel Sakr
 */

#ifndef DCMOTOR_H_
#define DCMOTOR_H_
#include "../MCAL/std_types.h"
typedef enum{
	stop,Clockwise,Anti_clockwise
}MOTOR_MODE;
typedef struct{
	uint8 DC_MOTOR_PORT;
	uint8 DC_MOTOR_PINA;
	uint8 DC_MOTOR_PINB;
	uint8 DC_MOTOR_PORT_EN;
	uint8 DC_MOTOR_PINE;
	MOTOR_MODE STATE;
}DcMotor_ID;
extern DcMotor_ID Door;
void DcMotor_init(DcMotor_ID *id );
void DcMotor_Rotate(DcMotor_ID *motor,MOTOR_MODE state,uint8 speed);
#endif /* DCMOTOR_H_ */
