/*
 * main.c
 *
 *  Created on: Oct 8, 2024
 *      Author: Abdelrhman Adel Sakr
 */


#include "smarthome.h"

int main(void) {
	/* Initialize hardware components */
	hardware_init();

	while (1) {
		/* Check for if there is flame or not */
		uint8 Flame = FlameSensor_getValue();
		/* If flame is detected, activate the alarm and display a critical alert */
		if (Flame) {
			Buzzer_on();
			LCD_displayStringRowColumn(0, 0,"Critical alert!     ");
			LCD_displayStringRowColumn(1, 0,"                    ");
		} else {
			/* Turn off the alarm if no flame is detected */
			Buzzer_off();
			/* If no flame is detected, proceed with normal operation */

			/* Read the light intensity and temperature */
			uint8 Light_intensity = LDR_getLightIntensity(LDR_sensor);
			uint8 Temprature = LM35_getTemperature(temp_sensor);

			/* Automatic Lighting Control */
			Automatic_Lighting_Control(Light_intensity);

			/* Control fan speed based on temperature */
			automatic_Fan_speed_control(Temprature);

			/* Display temperature and light intensity on the LCD */
			display_control(Temprature, Light_intensity);
		}
	}
	return 0;
}
