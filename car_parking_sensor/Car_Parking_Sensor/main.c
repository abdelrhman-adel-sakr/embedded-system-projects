/*
 * main.c
 *
 *  Created on: Oct 15, 2024
 *      Author: Abdelrhman Adel Sakr
 */
#include "std_types.h"
#include "common_macros.h"
#include "gpio.h"
#include "icu.h"
#include "Buzzer.h"
#include "LCD.h"
#include "LED.h"
#include "ultrasonic.h"
#include "util/delay.h"

int main(void) {
	LCD_init();
	LEDS_init(&Blue);
	LEDS_init(&Green);
	LEDS_init(&Red);
	Buzzer_init();
	Ultrasonic_init(&distance);
	uint16 reading =0;
	do {
			Ultrasonic_Trigger(&distance);
			reading = Ultrasonic_readDistance(&distance);
			_delay_ms(20);
		} while (reading == 0);
	while(1) {
		reading = Ultrasonic_readDistance(&distance);
		Ultrasonic_Trigger(&distance);
		if (reading <= 5) {
			LED_on(&Blue);
			LED_on(&Green);
			LED_on(&Red);
			Buzzer_on();
			LCD_displayStringRowColumn(0, 0, "STOP            ");
			LCD_displayStringRowColumn(1, 0, "                ");
			_delay_ms(200);
			LED_off(&Blue);
			LED_off(&Green);
			LED_off(&Red);
			_delay_ms(200);
		} else if (reading <= 10) {
			Buzzer_off();
			LED_on(&Blue);
			LED_on(&Green);
			LED_on(&Red);
			LCD_displayStringRowColumn(0,0,"distance= ");
						LCD_intgerToString(reading);
						LCD_displayString(" cm  ");
		} else if (reading <= 15) {
			Buzzer_off();
			LED_off(&Blue);
			LED_on(&Green);
			LED_on(&Red);
			LCD_displayStringRowColumn(0,0,"distance= ");
						LCD_intgerToString(reading);
						LCD_displayString(" cm ");
		}else if (reading <=20){
			Buzzer_off();
			LED_off(&Blue);
			LED_off(&Green);
			LED_on(&Red);
			LCD_displayStringRowColumn(0,0,"distance= ");
						LCD_intgerToString(reading);
						LCD_displayString(" cm ");
		}else{
			Buzzer_off();
			LED_off(&Blue);
			LED_off(&Green);
			LED_off(&Red);
			LCD_displayStringRowColumn(0,0,"distance= ");
						LCD_intgerToString(reading);
						LCD_displayString(" cm ");
		}
	}
	return 0;
}

