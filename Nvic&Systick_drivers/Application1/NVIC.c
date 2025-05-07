/*
 * NVIC.c
 *
 *  Created on: Nov 28, 2024
 *      Author: abdel
 */
#include "NVIC.h"
#include "tm4c123gh6pm_registers.h"

/* Base addresses for NVIC and System Control Block (SCB) registers */
#define NVIC_ISER_BASE       0xE000E100 /* Interrupt Set-Enable Registers */
#define NVIC_ICER_BASE       0xE000E180 /* Interrupt Clear-Enable Registers */
#define NVIC_IPR_BASE        0xE000E400 /* Interrupt Priority Registers */
#define SCB_SHCSR            (*((volatile uint32 *)0xE000ED24)) /* System Handler Control and State Register */
#define SCB_SHPR1            (*((volatile uint32 *)0xE000ED18)) /* System Handler Priority Registers */
#define SCB_SHPR2            (*((volatile uint32 *)0xE000ED1C))
#define SCB_SHPR3            (*((volatile uint32 *)0xE000ED20))

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
typedef uint8 NVIC_IRQType;

typedef uint8 NVIC_IRQPriorityType;

/* Function to enable Interrupt request for this specific IRQ */
void NVIC_EnableIRQ(NVIC_IRQType IRQ_Num) {
    uint8 regIndex = IRQ_Num / 32;
    uint8 bitPos = IRQ_Num % 32;
    *((volatile uint32 *)(NVIC_ISER_BASE + (regIndex * 4))) = (1 << bitPos);
}

/* Function to disable Interrupt request for this specific IRQ */
void NVIC_DisableIRQ(NVIC_IRQType IRQ_Num) {
    uint8 regIndex = IRQ_Num / 32;
    uint8 bitPos = IRQ_Num % 32;
    *((volatile uint32 *)(NVIC_ICER_BASE + (regIndex * 4))) = (1 << bitPos);
}

/* Function to set the priority value for specific IRQ */
void NVIC_SetPriorityIRQ(NVIC_IRQType IRQ_Num, NVIC_IRQPriorityType IRQ_Priority) {
    uint8 regIndex = IRQ_Num / 4;
    uint8 byteOffset = (IRQ_Num % 4) * 8;
    volatile uint8 *priorityReg = (volatile uint8 *)(NVIC_IPR_BASE + (regIndex * 4) + byteOffset);
    *priorityReg = IRQ_Priority << 5; // Only upper 3 bits are used for priority
}

/* Function to enable specific ARM system or fault exceptions */
void NVIC_EnableException(NVIC_ExceptionType Exception_Num) {
    switch (Exception_Num) {
        case EXCEPTION_MEM_FAULT_TYPE:
            SCB_SHCSR |= MEM_FAULT_ENABLE_MASK;
            break;
        case EXCEPTION_BUS_FAULT_TYPE:
            SCB_SHCSR |= BUS_FAULT_ENABLE_MASK;
            break;
        case EXCEPTION_USAGE_FAULT_TYPE:
            SCB_SHCSR |= USAGE_FAULT_ENABLE_MASK;
            break;
        default:
            /* Other exceptions like SysTick or NMI are always enabled by hardware */
            break;
    }
}

/* Function to disable specific ARM system or fault exceptions */
void NVIC_DisableException(NVIC_ExceptionType Exception_Num) {
    switch (Exception_Num) {
        case EXCEPTION_MEM_FAULT_TYPE:
            SCB_SHCSR &= ~MEM_FAULT_ENABLE_MASK;
            break;
        case EXCEPTION_BUS_FAULT_TYPE:
            SCB_SHCSR &= ~BUS_FAULT_ENABLE_MASK;
            break;
        case EXCEPTION_USAGE_FAULT_TYPE:
            SCB_SHCSR &= ~USAGE_FAULT_ENABLE_MASK;
            break;
        default:
            /* Other exceptions like SysTick or NMI cannot be disabled by software */
            break;
    }
}

/* Function to set the priority value for specific ARM system or fault exceptions */
void NVIC_SetPriorityException(NVIC_ExceptionType Exception_Num, NVIC_ExceptionPriorityType Exception_Priority) {
    switch (Exception_Num) {
        case EXCEPTION_MEM_FAULT_TYPE:
            SCB_SHPR1 = (SCB_SHPR1 & ~MEM_FAULT_PRIORITY_MASK) |
                        ((Exception_Priority << MEM_FAULT_PRIORITY_BITS_POS) & MEM_FAULT_PRIORITY_MASK);
            break;
        case EXCEPTION_BUS_FAULT_TYPE:
            SCB_SHPR1 = (SCB_SHPR1 & ~BUS_FAULT_PRIORITY_MASK) |
                        ((Exception_Priority << BUS_FAULT_PRIORITY_BITS_POS) & BUS_FAULT_PRIORITY_MASK);
            break;
        case EXCEPTION_USAGE_FAULT_TYPE:
            SCB_SHPR1 = (SCB_SHPR1 & ~USAGE_FAULT_PRIORITY_MASK) |
                        ((Exception_Priority << USAGE_FAULT_PRIORITY_BITS_POS) & USAGE_FAULT_PRIORITY_MASK);
            break;
        case EXCEPTION_SVC_TYPE:
            SCB_SHPR2 = (SCB_SHPR2 & ~SVC_PRIORITY_MASK) |
                        ((Exception_Priority << SVC_PRIORITY_BITS_POS) & SVC_PRIORITY_MASK);
            break;
        case EXCEPTION_PEND_SV_TYPE:
            SCB_SHPR3 = (SCB_SHPR3 & ~PENDSV_PRIORITY_MASK) |
                        ((Exception_Priority << PENDSV_PRIORITY_BITS_POS) & PENDSV_PRIORITY_MASK);
            break;
        case EXCEPTION_SYSTICK_TYPE:
            SCB_SHPR3 = (SCB_SHPR3 & ~SYSTICK_PRIORITY_MASK) |
                        ((Exception_Priority << SYSTICK_PRIORITY_BITS_POS) & SYSTICK_PRIORITY_MASK);
            break;
        default:
            /* Unsupported exception types */
            break;
    }
}
