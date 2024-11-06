/*
 * main.c
 * Control.c
 * Created on: Nov 1, 2024
 * Author: Abdelrhman Adel Sakr
 */
#include "MCAL/uart.h"
#include "HAL/external_eeprom.h"
#include "MCAL/PWM.h"
#include "HAL/DCmotor.h"
#include "HAL/PIR.h"
#include "MCAL/TIMER.h"
#include <util/delay.h>
#include <avr/io.h>

#define PASSWORD_LENGTH 5
#define EEPROM_ADDRESS_START 0x0311  // EEPROM start address for password storage
#define MAX_ATTEMPTS 3
#define LOCKOUT_TIME 60  // 1-minute lockout duration
#define DOOR_OPEN_TIME 15 // Door open time in ticks
#define DOOR_CLOSE_TIME 15 // Door close time in ticks

typedef enum {
	IDLE,
	VERIFY_PASSWORD,
	ENTER_PASSWORD,
	CHANGE_PASSWORD,
	DOOR_OPEN,
	DOOR_CLOSE,
	LOCKOUT
} ControlState;

ControlState state = IDLE;
uint8 tick = 0;
uint8 attempt_count = 0;

void timer_callback();

int main(void) {
	SREG |= (1 << 7);
	Buzzer_init();
	UART_ConfigType uart_config = { UART_8Bit, UART_Parity_disable,
			UART_ONE_STOP_BIT, UART_BaudRate };
	UART_init(&uart_config);
	DcMotor_init(&Door);
	PIR_init(&pir_config);
	Timer_ConfigType timer_config = { 0, 7813, TIMER1, NO_CLOCK, COMPARE_MODE };
	Timer_init(&timer_config);
	Timer_setCallBack(timer_callback, TIMER1);

	uint8 password1[PASSWORD_LENGTH];
	uint8 password2[PASSWORD_LENGTH];
	uint8 stored_password[PASSWORD_LENGTH];
	uint8 match;
	uint8 mood;

	while (1) {
		switch (state) {
		case IDLE:
			// Receive passwords from HMI ECU
			for (uint8 i = 0; i < PASSWORD_LENGTH; i++) {
				password1[i] = UART_recieveByte();
			}
			for (uint8 j = 0; j < PASSWORD_LENGTH; j++) {
				password2[j] = UART_recieveByte();
			}
			state = VERIFY_PASSWORD;
			break;

		case VERIFY_PASSWORD:
			match = 1;
			for (uint8 i = 0; i < PASSWORD_LENGTH; i++) {
				if (password1[i] != password2[i]) {
					match = 0;
					break;
				}
			}

			UART_sendByte(match);  // Send match result
			if (match) {
				// Store password in EEPROM
				for (uint8 z = 0; z < PASSWORD_LENGTH; z++) {
					uint8 status = EEPROM_writeByte(EEPROM_ADDRESS_START + z,
							password1[z]);
					if (status != SUCCESS) {
						while (1)
							; // Halt on error
					}
					_delay_ms(10);
				}
				state = ENTER_PASSWORD;
			} else {
				state = IDLE;
			}
			break;

		case ENTER_PASSWORD:
			mood = UART_recieveByte();
			// Load stored password from EEPROM
			for (uint8 z = 0; z < PASSWORD_LENGTH; z++) {
				EEPROM_readByte(EEPROM_ADDRESS_START + z, &stored_password[z]);
			}

			uint8 match2 = 1;
			for (uint8 x = 0; x < PASSWORD_LENGTH; x++) {
				uint8 K = UART_recieveByte();
				_delay_ms(20);
				if (K != stored_password[x]) {
					match2 = 0;
				}
			}

			if (match2) {
				attempt_count = 0;
				UART_sendByte(1);
				if (mood == 0) {//see which mood the user choose
					state = DOOR_OPEN;
				} else {
					state = CHANGE_PASSWORD;
				}
			} else {
				attempt_count++;
				if (attempt_count == MAX_ATTEMPTS) {
					state = LOCKOUT;
					attempt_count = 0;
				}else{
					state = ENTER_PASSWORD;
				}
				UART_sendByte(0);

			}
			break;
		case CHANGE_PASSWORD:

			// Store password in EEPROM
			for (uint8 z = 0; z < PASSWORD_LENGTH; z++) {
				uint8 status = EEPROM_writeByte(EEPROM_ADDRESS_START + z,
						password1[z]);
				if (status != SUCCESS) {
					while (1)
						; // Halt on error
				}
				_delay_ms(10);
			}
			state = IDLE;
			break;
		case DOOR_OPEN:
			tick = 0;
			DcMotor_Rotate(&Door, Clockwise, 100);  // Open the door
			Timer_start(TIMER1, F_CPU_1024);
			UART_sendByte(1);
			_delay_ms(50);
			tick = 0;
			while (tick <= DOOR_OPEN_TIME)
				;  // Stop motor after defined time
			DcMotor_Rotate(&Door, stop, 0);
			// Wait for PIR sensor to detect motion
			while (PIR_getState() == 1) {
				// Wait until no motion is detected
			}
			UART_sendByte(0);
			_delay_ms(50);
			tick = 0;  // Reset tick for door close timing
			state = DOOR_CLOSE;
			break;

		case DOOR_CLOSE:
			DcMotor_Rotate(&Door, Anti_clockwise, 100);  // Close the door
			while (tick <= DOOR_CLOSE_TIME)
				;  // Stop motor after defined time
			DcMotor_Rotate(&Door, stop, 0);  // Stop motor
			tick = 0;
			Timer_stop(TIMER1);
			state = ENTER_PASSWORD;
			break;

		case LOCKOUT:
			Buzzer_on();
			tick = 0;
			Timer_start(TIMER1, F_CPU_1024);
			while (tick <= LOCKOUT_TIME)
				; // Wait for lockout duration
			Buzzer_off();
			Timer_stop(TIMER1);
			tick = 0;
			state = ENTER_PASSWORD;
			break;
		}
	}
}

void timer_callback() {
	tick++;
}
