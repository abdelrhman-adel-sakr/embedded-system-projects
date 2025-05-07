/*
 * Systick.h
 *
 *  Created on: Nov 28, 2024
 *      Author: Abdelrhman Adel Sakr
 */
#ifndef SYSTICK_H_
#define SYSTICK_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define SYSTICK_CTRL_REG          (*((volatile uint32 *)0xE000E010)) /* SysTick Control and Status Register */
#define SYSTICK_RELOAD_REG        (*((volatile uint32 *)0xE000E014)) /* SysTick Reload Value Register */
#define SYSTICK_CURRENT_REG       (*((volatile uint32 *)0xE000E018)) /* SysTick Current Value Register */

#define SYSTICK_CLK_SRC           0x00000004 /* Clock Source: Processor Clock */
#define SYSTICK_ENABLE            0x00000001 /* Enable SysTick */
#define SYSTICK_TICK_INT          0x00000002 /* Enable SysTick Interrupt */

/*******************************************************************************
 *                              Function Prototypes                            *
 *******************************************************************************/

/**
 * brief Initialize the SysTick timer with the specified time in milliseconds using interrupts.
 *
 * param a_TimeInMilliSeconds Time interval in milliseconds.
 */
void SysTick_Init(uint16 a_TimeInMilliSeconds);

/**
 * brief Start a busy-wait (polling-based) delay for the specified time in milliseconds.
 *
 * param a_TimeInMilliSeconds Time interval in milliseconds.
 */
void SysTick_StartBusyWait(uint16 a_TimeInMilliSeconds);

/**
 * brief Set the callback function to be executed in the SysTick interrupt handler.
 *
 * param Ptr2Func Pointer to the callback function.
 */
void SysTick_SetCallBack(volatile void (*Ptr2Func)(void));

/**
 * brief Start or resume the SysTick timer.
 */
void SysTick_Start(void);

/**
 * brief Stop the SysTick timer.
 */
void SysTick_Stop(void);

/**
 * brief De-initialize the SysTick timer.
 */
void SysTick_DeInit(void);

/**
 * brief SysTick interrupt handler.
 */
void SysTick_Handler(void);

#endif /* SYSTICK_H_ */
