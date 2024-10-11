/*
 * smarthome.h
 *
 *  Created on: Oct 3, 2024
 *      Author: Abdelrhman Adel Sakr
 */

#ifndef SMARTHOME_H_
#define SMARTHOME_H_
#include"LCD.h"
#include"gpio.h"
#include"common_macros.h"
#include "lm35_sensor.h"
#include "LDR.h"
#include "ADC.h"
#include "LED.h"
#include <util/delay.h>
#include "flamesensor.h"
#include "Buzzer.h"
#include "DCmotor.h"
#include <util/delay.h>
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/* Temperature thresholds for fan control */
#define TEMP_THRESHOLD_LOW 25
#define TEMP_THRESHOLD_MEDIUM 30
#define TEMP_THRESHOLD_HIGH 35
#define TEMP_THRESHOLD_MAX 40

/* Light intensity thresholds for lighting control */
#define LIGHT_HIGH_INTENSITY 75
#define LIGHT_MEDIUM_INTENSITY 50
#define LIGHT_LOW_INTENSITY 15

/*******************************************************************************
 *                            Functions Prototypes                             *
 *******************************************************************************/

/*
 *  Initializes hardware components (LEDs, Fan, Buzzer, etc.).
 */
void hardware_init(void);

/*
 * Controls LEDs based on light intensity.
 */
void Automatic_Lighting_Control(uint8 Light_intensity);

/*
 * Updates LCD with fan status, temperature, and light intensity.
 */
void display_control(uint8 temp, uint8 intensity);

/*
 * Adjusts fan speed based on temperature.
 */
void automatic_Fan_speed_control(uint8 temp);

#endif /* SMARTHOME_H_ */
