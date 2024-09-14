/*
 * miniproject2.c
 *
 *  Created on: Sep 9, 2024
 *      Author: Abdelrhman adel sakr
 */
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
unsigned char sec = 0, hour = 0, min = 0, secu = 0, sect = 0, minu = 0,mint = 0, houru = 0, hourt = 0;
unsigned char pressed = 0,TIMER_ISR=0;
void desplay7(void) {
	PORTA &= ~(1 << PA5);
	PORTA |= (1 << PA0);
	PORTC = (PORTC & 0xF0) | (hourt & 0x0F);
	_delay_ms(2);
	PORTA &= ~(1 << PA0);
	PORTA |= (1 << PA1);
	PORTC = (PORTC & 0xF0) | (houru & 0x0F);
	_delay_ms(2);
	PORTA &= ~(1 << PA1);
	PORTA |= (1 << PA2);
	PORTC = (PORTC & 0xF0) | (mint & 0x0F);
	_delay_ms(2);
	PORTA &= ~(1 << PA2);
	PORTA |= (1 << PA3);
	PORTC = (PORTC & 0xF0) | (minu & 0x0F);
	_delay_ms(2);
	PORTA &= ~(1 << PA3);
	PORTA |= (1 << PA4);
	PORTC = (PORTC & 0xF0) | (sect & 0x0F);
	_delay_ms(2);
	PORTA &= ~(1 << PA4);
	PORTA |= (1 << PA5);
	PORTC = (PORTC & 0xF0) | (secu & 0x0F);
	_delay_ms(2);
}
ISR(INT0_vect) {
	secu = 0, sect = 0, minu = 0, mint = 0, houru = 0, hourt = 0;
}
ISR(INT1_vect) {
	TCCR1B = (1 << WGM12);
}
ISR(INT2_vect) {
	TCCR1B = (1 << WGM12) | (1 << CS12);
}
ISR(TIMER1_COMPA_vect) {
	TIMER_ISR=1;
}
void INT0_Init(void) {
	MCUCR |= (1 << ISC01); //TRigger INT0 with falling edge
	MCUCR &= ~(1 << ISC00);
	GICR |= (1 << INT0); // enable external interrupt pin INT0
	SREG |= (1 << 7);
}
void INT1_Init(void) {
	MCUCR |= (1 << ISC11); //Trigger INT1 with raisig edge
	MCUCR |= (1 << ISC10);
	GICR |= (1 << INT1);    // Enable external interrupt pin INT1
}
void INT2_Init(void) {
	DDRB &= (~(1 << PB2));
	GICR |= (1 << INT2); //Enable INT2 with falling edge
	MCUCSR &= ~(1 << ISC2); //Trigger INT2 with falling edge
}
void TIMER1_CTC_Init(void) { //I will use a pre scall of N=256 then i will need 62500 iteration to get 1 sec
	TCNT1 = 0;
	OCR1A = 62500;
	TIMSK |= (1 << OCIE1A); //enable timer1 compare interrupt
	TCCR1A = 0;
	TCCR1B = (1 << WGM12) | (1 << CS12);
}
void AVR_PINS(void){
	    DDRA |= 0xEF;
		DDRB &= 0x00;
		DDRC |= 0x0F;
		DDRD &= ~(1 << PD2);
		DDRD &= ~(1 << PD3);
		DDRD |= (1 << PD4);
		DDRD |= (1 << PD5);
		PORTD &= ~(1 << PD3); //turn off internal pull up resistor at PD3
		PORTD |= (1 << PD2);  // Activate the internal pull up resistor at PD2
		PORTB |=0xFF;    // Activate the internal pull up resistor at pin B
		PORTC &= 0xF0;    //initial seven segmengt value 0
		PORTD |= (1 << PD4);
}
void INC_DEC(void){
	if (!(PINB & (1 << 7))) {
					if (pressed == 0) {
						pressed = 1;
					}
					else {
						pressed = 0;
					}
					while (!(PINB & (1 << PB7))) {
						desplay7();
					}
				}
			if (!(PINB & (1 << PB1))) {
				while (!(PINB & (1 << PB1))) {
					desplay7();
				}
				houru++;
				if (houru == 10) {
					houru = 0;
					hourt++;
				}
			}
			if (!(PINB & (1 << PB0))) {
				while (!(PINB & (1 << PB0))) {
					desplay7();
				}
				if (houru == 0) {
					if (hourt > 0) {
						hourt--;
						houru = 9;
					}
				} else {
					houru--;
				}
			}
			if (!(PINB & (1 << PB4))) {
				while (!(PINB & (1 << PB4))) {
					desplay7();
				}
				minu++;
				if (minu == 10) {
					minu = 0;
					mint++;
				}
			}
			if (!(PINB & (1 << PB3))) {
				while (!(PINB & (1 << PB3))) {
					desplay7();
				}
				if (minu == 0) {
					if (mint > 0) {
						mint--;
						minu = 9;
					}
				} else {
					minu--;
				}
			}
			if (!(PINB & (1 << PB6))) {
				while (!(PINB & (1 << PB6))) {
					desplay7();
				}
				secu++;
				if (secu == 10) {
					secu = 0;
					sect++;
				}
			}
			if (!(PINB & (1 << PB5))) {
				while (!(PINB & (1 << PB5))) {
					desplay7();
				}
					if (secu == 0) {
						if (sect > 0) {
							sect--;
							secu = 9;
						}
					} else {
						secu--;
					}
			}
}
int main(void) {
	SREG |= (1 << 7); //Enable interrupts by setting I-bit
	INT2_Init();
	INT1_Init();
	INT0_Init();
	TIMER1_CTC_Init();
	AVR_PINS();
	while (1) {
		if(TIMER_ISR==1){
			if (pressed == 0) {
					PORTD |= (1 << PD4); //light up the count up led
					PORTD &= ~(1 << PD5); // turn off count down led
					PORTD &= ~(1 << PD0); //turn off the alarm
					secu++;//every tick increase 1 sec
					if (secu == 10) {
						secu = 0;
						sect++;
					}
					if (sect == 6) {
						sect = 0;
						minu++;
					}
					if (minu == 10) {
						minu = 0;
						mint++;
					}
					if (mint == 6) {
						mint = 0;
						hour++;
						houru++;
					}
					if (houru == 10) {
						houru = 0;
						hourt++;
					}
				}
				if (pressed == 1) {
					PORTD |= (1 << PD5); //light up the count down led
					PORTD &= ~(1 << PD4); //turn off the count up led
				if (secu != 0 || sect != 0 || minu != 0 || mint != 0 || houru != 0|| hourt != 0) {
						// Decrement seconds
				if (secu == 0) {
						secu = 9;
					if (sect == 0) {
						sect = 5;
						// Decrement minutes
						if (minu == 0) {
							minu = 9;
							if (mint == 0) {
								mint = 5;
							// Decrement hours
							if (houru == 0) {
								houru = 9;
								if (hourt != 0) {
									hourt--;
									}
								} else {
									houru--;
									}
							} else {
									mint--;
									}
								} else {
									minu--;
								}
							} else {
								sect--;
							}
						} else {
							secu--;
						}
					} else {
						// If countdown reaches zero, activate the alarm
						PORTD |= (1 << PD0);  // Turn on the alarm
						secu = 0, sect = 0, minu = 0, mint = 0, houru = 0, hourt = 0;
						while (!(PINB & (1 << PB7))) {  // Infinite loop to stop the timer
							desplay7();
						}
					}
				}
				TIMER_ISR=0;
			}
		INC_DEC();
		desplay7();
	}
}
