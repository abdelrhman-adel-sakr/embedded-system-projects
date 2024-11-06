/*
 * PIR.h
 *
 *  Created on: Oct 25, 2024
 *      Author: Abdelrhman Adel Sakr
 */

#ifndef HAL_PIR_H_
#define HAL_PIR_H_

#include "../MCAL/std_types.h"
#include "../MCAL/gpio.h"

typedef struct {
    uint8 PIR_PORT;
    uint8 PIR_PIN;
} PIR_ConfigType;
extern PIR_ConfigType pir_config;
// Function prototypes
void PIR_init(const PIR_ConfigType *config);
uint8 PIR_getState(void);
#endif /* HAL_PIR_H_ */
