/*
 * Systick.c
 *
 *  Created on: Nov 28, 2024
 *      Author: Abdelrhman Adel Sakr
 */
#include "Systick.h"

/*******************************************************************************
 *                           Static Global Variables                           *
 *******************************************************************************/

/* Pointer to SysTick callback function */
static volatile void (*g_SysTick_CallBack)(void) = NULL_PTR;

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void SysTick_Init(uint16 a_TimeInMilliSeconds) {
    uint32 ticks = (16000 * a_TimeInMilliSeconds) - 1; /* Convert ms to clock ticks (16 MHz system clock) */
    SYSTICK_RELOAD_REG = ticks;                       /* Load the value into the Reload register */
    SYSTICK_CURRENT_REG = 0;                          /* Clear the current value register */
    SYSTICK_CTRL_REG = SYSTICK_CLK_SRC | SYSTICK_TICK_INT | SYSTICK_ENABLE; /* Enable SysTick with interrupt */
}

void SysTick_StartBusyWait(uint16 a_TimeInMilliSeconds) {
    uint32 ticks = (16000 * a_TimeInMilliSeconds) - 1; /* Convert ms to clock ticks (16 MHz system clock) */
    SYSTICK_RELOAD_REG = ticks;                       /* Load the value into the Reload register */
    SYSTICK_CURRENT_REG = 0;                          /* Clear the current value register */
    SYSTICK_CTRL_REG = SYSTICK_CLK_SRC | SYSTICK_ENABLE; /* Enable SysTick without interrupt */

    /* Wait until the COUNT flag is set */
    while ((SYSTICK_CTRL_REG & 0x10000) == 0);

    SYSTICK_CTRL_REG &= ~SYSTICK_ENABLE; /* Stop SysTick after busy-wait */
}

void SysTick_SetCallBack(volatile void (*Ptr2Func)(void)) {
    g_SysTick_CallBack = Ptr2Func; /* Set the global callback function pointer */
}

void SysTick_Start(void) {
    SYSTICK_CTRL_REG |= SYSTICK_ENABLE; /* Set the ENABLE bit to start SysTick */
}

void SysTick_Stop(void) {
    SYSTICK_CTRL_REG &= ~SYSTICK_ENABLE; /* Clear the ENABLE bit to stop SysTick */
}

void SysTick_DeInit(void) {
    SYSTICK_CTRL_REG = 0; /* Disable SysTick and clear all configuration */
    SYSTICK_RELOAD_REG = 0; /* Clear the Reload register */
    SYSTICK_CURRENT_REG = 0; /* Clear the Current Value register */
    g_SysTick_CallBack = NULL_PTR; /* Clear the callback function pointer */
}

void SysTick_Handler(void) {
    if (g_SysTick_CallBack != NULL_PTR) {
        g_SysTick_CallBack(); /* Call the user-defined callback function */
    }
}




