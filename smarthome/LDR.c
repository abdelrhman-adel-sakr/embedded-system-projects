/*
 * LDR.c
 *
 *  Created on: Oct 4, 2024
 *      Author: Abdelrhma Adel Sakr
 */
#include "LDR.h"
#include "ADC.h"
uint8 LDR_sensor=0;
uint8 LDR_getLightIntensity(uint8 LDR_Channel1){
     uint16 sensor_value=0;
     uint16 adc_value = 0;

     	/* Read ADC channel where the temperature sensor is connected */
     	adc_value = ADC_readchannel(LDR_Channel1);

     	/* Calculate the temperature from the ADC value*/
     	sensor_value = (uint8)(((uint32)adc_value*LDR_SENSOR_MAX_LIGHT_INTENSITY*ADC_REF_VOLT_VALUE)/(ADC_MAXIMUM_VALUE*LDR_SENSOR_MAX_VOLT_VALUE));
	return sensor_value;
}

