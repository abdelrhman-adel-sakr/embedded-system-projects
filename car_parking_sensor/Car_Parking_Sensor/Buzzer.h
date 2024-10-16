/*
 * Buzzer.h
 *
 *  Created on: Oct 5, 2024
 *      Author: Abdelrhman Adel Sakr
 */

#ifndef BUZZER_H_
#define BUZZER_H_
#include "std_types.h"
#define BUZZER_PIN_ID PIN5_ID
#define BUZZER_PORT_ID PORTC_ID
void Buzzer_init(void);
void Buzzer_on(void);
void Buzzer_off(void);
#endif /* BUZZER_H_ */
