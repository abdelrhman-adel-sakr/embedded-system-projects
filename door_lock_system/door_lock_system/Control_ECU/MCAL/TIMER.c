/*
 * TIMER.c
 *
 *  Created on: Oct 26, 2024
 *      Author: Abdelrhman Adel Sakr
 */
#include"TIMER.h"
#include <avr/io.h>
#include <avr/interrupt.h>
Timer_ConfigType Timer_cofig={.timer_InitialValue=0,.timer_compare_MatchValue=250,.timer_ID=TIMER0,.timer_clock=F_CPU_8,.timer_mode=COMPARE_MODE};
static void (*g_Timer0CallBack)(void) = NULL_PTR;
static void (*g_Timer1CallBack)(void) = NULL_PTR;
static void (*g_Timer2CallBack)(void) = NULL_PTR;

void Timer_init(const Timer_ConfigType *Config_Ptr) {
	SREG|=(1<<7);
    switch (Config_Ptr->timer_ID) {
        case TIMER0:
            TCNT0 = Config_Ptr->timer_InitialValue;
            if (Config_Ptr->timer_mode == NORMAL_MODE) {
                TCCR0 = (1 << FOC0) | Config_Ptr->timer_clock;
                TIMSK |= (1 << TOIE0); // Enable overflow interrupt
            } else {
                OCR0 = Config_Ptr->timer_compare_MatchValue;
                TCCR0 = (1 << WGM01) | (1 << FOC0) | Config_Ptr->timer_clock;
                TIMSK |= (1 << OCIE0); // Enable compare match interrupt
            }
            break;

        case TIMER1:
            TCNT1 = Config_Ptr->timer_InitialValue;
            if (Config_Ptr->timer_mode == NORMAL_MODE) {
                TCCR1A = (1 << FOC1A) | (1 << FOC1B);
                TCCR1B = Config_Ptr->timer_clock;
                TIMSK |= (1 << TOIE1); // Enable overflow interrupt
            } else {
                OCR1A = Config_Ptr->timer_compare_MatchValue;
                TCCR1A = (1 << FOC1A) | (1 << FOC1B);
                TCCR1B = (1 << WGM12) | Config_Ptr->timer_clock;
                TIMSK |= (1 << OCIE1A); // Enable compare match interrupt
            }
            break;

        case TIMER2:
            TCNT2 = Config_Ptr->timer_InitialValue;
            if (Config_Ptr->timer_mode == NORMAL_MODE) {
                TCCR2 = (1 << FOC2) | Config_Ptr->timer_clock;
                TIMSK |= (1 << TOIE2); // Enable overflow interrupt
            } else {
                OCR2 = Config_Ptr->timer_compare_MatchValue;
                TCCR2 = (1 << WGM21) | (1 << FOC2) | Config_Ptr->timer_clock;
                TIMSK |= (1 << OCIE2); // Enable compare match interrupt
            }
            break;
    }
}

void Timer_deInit(Timer_ID_Type timer_type) {
    switch (timer_type) {
        case TIMER0:
            TCCR0 = 0;
            TIMSK &= ~(1 << TOIE0) & ~(1 << OCIE0); // Disable all TIMER0 interrupts
            break;

        case TIMER1:
            TCCR1A = 0;
            TCCR1B = 0;
            TIMSK &= ~(1 << TOIE1) & ~(1 << OCIE1A); // Disable all TIMER1 interrupts
            break;

        case TIMER2:
            TCCR2 = 0;
            TIMSK &= ~(1 << TOIE2) & ~(1 << OCIE2); // Disable all TIMER2 interrupts
            break;
    }
}

void Timer_setCallBack(void(*a_ptr)(void), Timer_ID_Type a_timer_ID) {
    switch (a_timer_ID) {
        case TIMER0:
            g_Timer0CallBack = a_ptr;
            break;
        case TIMER1:
            g_Timer1CallBack = a_ptr;
            break;
        case TIMER2:
            g_Timer2CallBack = a_ptr;
            break;
    }
}

void Timer_start(Timer_ID_Type timer_id, Timer_ClockType timer_clock) {
    switch (timer_id) {
        case TIMER0:
            TCCR0 |= timer_clock; // Set the clock prescaler to start TIMER0
            break;
        case TIMER1:
            TCCR1B |= timer_clock; // Set the clock prescaler to start TIMER1
            break;
        case TIMER2:
            TCCR2 |= timer_clock; // Set the clock prescaler to start TIMER2
            break;
        default:
            // Handle invalid timer ID if necessary
            break;
    }
}

void Timer_stop(Timer_ID_Type timer_id) {
    switch (timer_id) {
        case TIMER0:
            TCCR0 &= ~((1 << CS02) | (1 << CS01) | (1 << CS00)); // Clear clock prescaler bits to stop TIMER0
            break;
        case TIMER1:
            TCCR1B &= ~((1 << CS12) | (1 << CS11) | (1 << CS10)); // Clear clock prescaler bits to stop TIMER1
            break;
        case TIMER2:
            TCCR2 &= ~((1 << CS22) | (1 << CS21) | (1 << CS20)); // Clear clock prescaler bits to stop TIMER2
            break;
        default:
            // Handle invalid timer ID if necessary
            break;
    }
}

// ISR for TIMER0 Overflow
ISR(TIMER0_OVF_vect) {
    if (g_Timer0CallBack != NULL_PTR) {
        g_Timer0CallBack();
    }
}

// ISR for TIMER0 Compare Match
ISR(TIMER0_COMP_vect) {
    if (g_Timer0CallBack != NULL_PTR) {
        g_Timer0CallBack();
    }
}

// ISR for TIMER1 Overflow
ISR(TIMER1_OVF_vect) {
    if (g_Timer1CallBack != NULL_PTR) {
        g_Timer1CallBack();
    }
}

// ISR for TIMER1 Compare Match
ISR(TIMER1_COMPA_vect) {
    if (g_Timer1CallBack != NULL_PTR) {
        g_Timer1CallBack();
    }
}

// ISR for TIMER2 Overflow
ISR(TIMER2_OVF_vect) {
    if (g_Timer2CallBack != NULL_PTR) {
        g_Timer2CallBack();
    }
}

// ISR for TIMER2 Compare Match
ISR(TIMER2_COMP_vect) {
    if (g_Timer2CallBack != NULL_PTR) {
        g_Timer2CallBack();
    }
}
