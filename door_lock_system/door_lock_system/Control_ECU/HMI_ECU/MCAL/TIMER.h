/*
 * TIMER.h
 *
 *  Created on: Oct 26, 2024
 *      Author: Abdelrhman Adel Sakr
 */

#ifndef MCAL_TIMER_H_
#define MCAL_TIMER_H_
#include"std_types.h"

typedef enum {
    TIMER0,
    TIMER1,
    TIMER2
} Timer_ID_Type;

typedef enum {
    NORMAL_MODE,
    COMPARE_MODE
} Timer_ModeType;

typedef enum {
    NO_CLOCK,
    F_CPU_CLOCK,
    F_CPU_8,
    F_CPU_64,
    F_CPU_256,
    F_CPU_1024
} Timer_ClockType;

typedef struct {
    uint16 timer_InitialValue;
    uint16 timer_compare_MatchValue; // Used in compare mode only
    Timer_ID_Type timer_ID;
    Timer_ClockType timer_clock;
    Timer_ModeType timer_mode;
} Timer_ConfigType;

extern Timer_ConfigType Timer_cofig;
// Initialize the Timer with the specified configuration
void Timer_init(const Timer_ConfigType *Config_Ptr);

// Disable the specified Timer
void Timer_deInit(Timer_ID_Type timer_type);

// Set the callback function for the specified Timer
void Timer_setCallBack(void(*a_ptr)(void), Timer_ID_Type a_timer_ID);

// Function to start the timer
void Timer_start(Timer_ID_Type timer_id, Timer_ClockType timer_clock);

// Function to stop the timer
void Timer_stop(Timer_ID_Type timer_id);

#endif /* MCAL_TIMER_H_ */
