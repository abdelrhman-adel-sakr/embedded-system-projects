/*
 * NVIC.c
 *
 *  Created on: Nov 28, 2024
 *      Author: abdelrhman adel sakr
 */
#include "NVIC.h"

/* Base addresses for NVIC and System Control Block (SCB) registers */
#define SCB_SHCSR            (*((volatile uint32 *)0xE000ED24)) /* System Handler Control and State Register */
#define SCB_SHPR1            (*((volatile uint32 *)0xE000ED18)) /* System Handler Priority Registers */
#define SCB_SHPR2            (*((volatile uint32 *)0xE000ED1C))
#define SCB_SHPR3            (*((volatile uint32 *)0xE000ED20))


/*******************************************************************************
 *                          Functions Implementation                           *
 *******************************************************************************/


/*********************************************************************
 * Service Name: Function to enable Interrupt request for this specific IRQ
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): IRQ_Num - Number of the IRQ from the target vector table
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to enable the Interrupt Request (IRQ) for a
 *              specific IRQ number.
 *********************************************************************/
void NVIC_EnableIRQ(NVIC_IRQType IRQ_Num)
{
    uint8 regIndex = IRQ_Num / 32;
    uint8 bitPos = IRQ_Num % 32;
    *((volatile uint32*) (NVIC_EN0_REG + (regIndex * 4))) = (1 << bitPos);
}

/*********************************************************************
 * Service Name: Function to disable Interrupt request for this specific IRQ
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): IRQ_Num - Number of the IRQ from the target vector table
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to disable the Interrupt Request (IRQ) for a
 *              specific IRQ number.
 *********************************************************************/
void NVIC_DisableIRQ(NVIC_IRQType IRQ_Num)
{
    uint8 regIndex = IRQ_Num / 32;
    uint8 bitPos = IRQ_Num % 32;
    *((volatile uint32*) (NVIC_DIS0_REG + (regIndex * 4))) = (1 << bitPos);
}

/*********************************************************************
 * Service Name: Function to set the priority value for specific IRQ
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): IRQ_Num - Number of the IRQ from the target vector table
 *                  IRQ_Priority - Priority value for the specific IRQ
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to set the priority for a specific IRQ.
 *********************************************************************/
void NVIC_SetPriorityIRQ(NVIC_IRQType IRQ_Num,
                         NVIC_IRQPriorityType IRQ_Priority)
{
    uint8 regIndex = IRQ_Num / 4;
        uint8 byteOffset = (IRQ_Num % 4) * 8;
        volatile uint8 *priorityReg = (volatile uint8 *)(NVIC_PRI0_REG + (regIndex * 4) + byteOffset);
        *priorityReg = IRQ_Priority << 5;
}

/*********************************************************************
 * Service Name: Function to enable specific ARM system or fault exceptions
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): Exception_Num - Number of the system exception
 *                                   from the exception table
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to enable a specific system or fault exception.
 *********************************************************************/
void NVIC_EnableException(NVIC_ExceptionType Exception_Num)
{
    switch (Exception_Num)
    {
    case EXCEPTION_MEM_FAULT_TYPE:
        NVIC_SYSTEM_SYSHNDCTRL |= MEM_FAULT_ENABLE_MASK;
        break;
    case EXCEPTION_BUS_FAULT_TYPE:
        NVIC_SYSTEM_SYSHNDCTRL |= BUS_FAULT_ENABLE_MASK;
        break;
    case EXCEPTION_USAGE_FAULT_TYPE:
        NVIC_SYSTEM_SYSHNDCTRL |= USAGE_FAULT_ENABLE_MASK;
        break;
    default:
        /* Unsupported exception */
        break;
    }
}

/*********************************************************************
 * Service Name: Function to disable specific ARM system or fault exceptions
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): Exception_Num - Number of the system exception
 *                                   from the exception table
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to disable a specific system or fault exception.
 *********************************************************************/
void NVIC_DisableException(NVIC_ExceptionType Exception_Num)
{
    switch (Exception_Num)
    {
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
        /* Unsupported exception */
        break;
    }
}

/*********************************************************************
 * Service Name: Function to set the priority value for specific ARM system or fault exceptions
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): Exception_Num - Number of the system exception
 *                                   from the exception table
 *                  Exception_Priority - Priority value for the system
 *                                       exception
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to set the priority for a specific system
 *              or fault exception.
 *********************************************************************/
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

        case EXCEPTION_DEBUG_MONITOR_TYPE:
            SCB_SHPR3 = (SCB_SHPR3 & ~DEBUG_MONITOR_PRIORITY_MASK) |
                        ((Exception_Priority << DEBUG_MONITOR_PRIORITY_BITS_POS) & DEBUG_MONITOR_PRIORITY_MASK);
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
