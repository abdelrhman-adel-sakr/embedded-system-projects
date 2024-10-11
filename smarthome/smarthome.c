/*
 * smarthome.c
 *
 *  Created on: Oct 3, 2024
 *      Author: Abdelrhman Adel Sakr
 */


#include "smarthome.h"
void hardware_init(void){
	LCD_init();
	ADC_init();
	Buzzer_init();
	DcMotor_init(&fan);
	FlameSensor_init();
	LEDS_init(&Red);
	LEDS_init(&Green);
	LEDS_init(&Blue);
}
void Automatic_Lighting_Control(uint8 Light_int){
	if(Light_int>LIGHT_HIGH_INTENSITY){
		LED_off(&Red);
		LED_off(&Green);
		LED_off(&Blue);
	}
	else if(Light_int>LIGHT_MEDIUM_INTENSITY){
		LED_on(&Red);
		LED_off(&Green);
		LED_off(&Blue);
	}
	else if(Light_int>LIGHT_LOW_INTENSITY){
		LED_on(&Red);
				LED_on(&Green);
				LED_off(&Blue);
	}
	else{

		LED_on(&Red);
				LED_on(&Green);
				LED_on(&Blue);
	}
}
void display_control(uint8 temp, uint8 intensity ){
	LCD_moveCursor(0,0);
if(temp>=TEMP_THRESHOLD_LOW){
	LCD_displayString("Fan is on");
}
else{
	LCD_displayString("Fan is off");
}
LCD_moveCursor(1,0);
LCD_displayString("Temp=");
LCD_intgerToString(temp);
if(temp<100){
	LCD_displayString(" ");
}
LCD_displayString("LDR=");
LCD_intgerToString(intensity);
LCD_displayCharacter('%');
if(intensity<100){
	LCD_displayString(" ");
}
}
void automatic_Fan_speed_control(uint8 temp){
uint8 speed=0;
MOTOR_MODE state=Clockwise;
if(temp>=TEMP_THRESHOLD_MAX){
	speed=100;
}
else if(temp>=TEMP_THRESHOLD_HIGH){
	speed=75;
}
else if(temp>=TEMP_THRESHOLD_MEDIUM){
	speed=50;
}
else if(temp>=TEMP_THRESHOLD_LOW){
	speed=25;
}
else{
	state=stop;
}
DcMotor_Rotate(&fan,state,speed);
}
 /* int main(void){
	 DcMotor_ID motor={PORTB_ID,PIN0_ID,PIN1_ID,PIN3_ID,Clockwise};
	 // uint16 ldr=0;
	 // uint8 temp=10;
	//LCD_init();
		//		  LCD_displayString("zeby manga");
			//	  LCD_intgerToString(20);
				  //LCD_displayStringRowColumn(1,1,"temp=");
	  DcMotor_init(&motor);
		  while(1){
			  DcMotor_Rotate(&motor,Clockwise,50);
			 // temp=LM35_getTemperature();
			//  ldr=LDR_getLightIntensity();
			 //LCD_displayStringRowColumn(1,0,"temp=");
			 //LCD_displayStringRowColumn(1,5,temp);
	  }

  }
*/
