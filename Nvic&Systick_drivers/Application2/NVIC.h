/*
 * NVIC.h
 *
 *  Created on: Nov 28, 2024
 *      Author: Abdelrhman Adel Sakr
 */
#ifndef NVIC_H_
#define NVIC_H_

/*******************************************************************************
 *                                Inclusions                                   *
 *******************************************************************************/
#include "std_types.h"
#include "tm4c123gh6pm_registers.h"

/*******************************************************************************
 *                           Preprocessor Definitions                          *
 *******************************************************************************/

#define MEM_FAULT_PRIORITY_MASK 0x000000E0
#define MEM_FAULT_PRIORITY_BITS_POS 5

#define BUS_FAULT_PRIORITY_MASK              0x0000E000
#define BUS_FAULT_PRIORITY_BITS_POS          13

#define USAGE_FAULT_PRIORITY_MASK            0x00E00000
#define USAGE_FAULT_PRIORITY_BITS_POS        21

#define SVC_PRIORITY_MASK                    0xE0000000
#define SVC_PRIORITY_BITS_POS                29

#define DEBUG_MONITOR_PRIORITY_MASK          0x000000E0
#define DEBUG_MONITOR_PRIORITY_BITS_POS      5

#define PENDSV_PRIORITY_MASK                 0x00E00000
#define PENDSV_PRIORITY_BITS_POS             21

#define SYSTICK_PRIORITY_MASK                0xE0000000
#define SYSTICK_PRIORITY_BITS_POS            29

#define MEM_FAULT_ENABLE_MASK                0x00010000
#define BUS_FAULT_ENABLE_MASK                0x00020000
#define USAGE_FAULT_ENABLE_MASK              0x00040000

#define NVIC_ISER_BASE       0xE000E100 /* Interrupt Set-Enable Registers */
#define NVIC_ICER_BASE       0xE000E180 /* Interrupt Clear-Enable Registers */
#define NVIC_IPR_BASE        0xE000E400 /* Interrupt Priority Registers */

/* Enable Exceptions ... This Macro enables IRQ interrupts, Programmable Systems Exceptions and Faults by clearing the I-bit in the PRIMASK. */
#define Enable_Exceptions()    __asm(" CPSIE I ")

/* Disable Exceptions ... This Macro disables IRQ interrupts, Programmable Systems Exceptions and Faults by setting the I-bit in the PRIMASK. */
#define Disable_Exceptions()   __asm(" CPSID I ")

/* Enable Faults ... This Macro enables Faults by clearing the F-bit in the FAULTMASK. */
#define Enable_Faults()        __asm(" CPSIE F ")

/* Disable Faults ... This Macro disables Faults by setting the F-bit in the FAULTMASK. */
#define Disable_Faults()       __asm(" CPSID F ")

/*******************************************************************************
 *                           Data Types Declarations                           *
 *******************************************************************************/
typedef uint8 NVIC_IRQType;

typedef uint8 NVIC_IRQPriorityType;

typedef enum
{
    EXCEPTION_RESET_TYPE,
    EXCEPTION_NMI_TYPE,
    EXCEPTION_HARD_FAULT_TYPE,
    EXCEPTION_MEM_FAULT_TYPE,
    EXCEPTION_BUS_FAULT_TYPE,
    EXCEPTION_USAGE_FAULT_TYPE,
    EXCEPTION_SVC_TYPE,
    EXCEPTION_DEBUG_MONITOR_TYPE,
    EXCEPTION_PEND_SV_TYPE,
    EXCEPTION_SYSTICK_TYPE
} NVIC_ExceptionType;

typedef uint8 NVIC_ExceptionPriorityType;

/*******************************************************************************
 *                           Function Prototypes                                *
 *******************************************************************************/

/* Function to enable Interrupt request for this specific IRQ */
void NVIC_EnableIRQ(NVIC_IRQType IRQ_Num);

/* Function to disable Interrupt request for this specific IRQ */
void NVIC_DisableIRQ(NVIC_IRQType IRQ_Num);

/* Function to set the priority value for specific IRQ */
void NVIC_SetPriorityIRQ(NVIC_IRQType IRQ_Num, NVIC_IRQPriorityType IRQ_Priority);

/* Function to enable specific ARM system or fault exceptions */
void NVIC_EnableException(NVIC_ExceptionType Exception_Num);

/* Function to disable specific ARM system or fault exceptions */
void NVIC_DisableException(NVIC_ExceptionType Exception_Num);

/* Function to set the priority value for specific ARM system or fault exceptions */
void NVIC_SetPriorityException(NVIC_ExceptionType Exception_Num, NVIC_ExceptionPriorityType Exception_Priority);

#endif /* NVIC_H_ */
