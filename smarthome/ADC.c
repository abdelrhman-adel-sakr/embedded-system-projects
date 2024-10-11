/*
 * ADC.c
 *
 *  Created on: Sep 28, 2024
 *      Author: Abdelrhman Adel Sakr
 */
#include"std_types.h"
#include"gpio.h"
#include"lcd.h"
#include"common_macros.h"
#include<avr/io.h>
void ADC_init(void){
    ADMUX = (1<<REFS0)|(1<<REFS1);//activate internal 2.56v vref
    ADCSRA = (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
    //|(1<<ADIE)
}
uint16 ADC_readchannel(uint8 ch_num){
	ADMUX=(ADMUX & 0xE0)|(ch_num & 0x1F);
	SET_BIT(ADCSRA,ADSC);
	while(BIT_IS_CLEAR(ADCSRA,ADIF));
	SET_BIT(ADCSRA,ADIF);
	return ADC;
}


