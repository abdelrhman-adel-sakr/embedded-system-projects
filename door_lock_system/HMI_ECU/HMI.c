/*
 * main.c
 *HMI.c
 *  Created on: Nov 1, 2024
 *      Author: Abdelrhman Adel
 */
#include "HAL/lcd.h"
#include "HAL/keypad.h"
#include "MCAL/uart.h"
#include "MCAL/TIMER.h"
#include "MCAL/std_types.h"
#include <util/delay.h>
#include <avr/io.h>
#define PASSWORD_LENGTH 5
#define ENTER_KEY '#'
#define MAX_ATTEMPTS 3
#define LOCKOUT_TIME 60 // 1-minute lockout
#define DOOR_OPEN_TIME 15
typedef enum {
	ENTER_PASSWORD,
	RE_ENTER_PASSWORD,
	WAIT_FOR_CONFIRMATION,
	MAIN_OPTIONS,
	OPEN_DOOR,
	CHANGE_PASSWORD
} SystemState;

SystemState state = ENTER_PASSWORD;
uint8 tick = 0;
uint8 attempt_count = 0;

void timer_callback();

int main(void) {
	SREG |= (1 << 7);
	LCD_init();
	UART_ConfigType uart_config = { UART_8Bit, UART_Parity_disable,
			UART_ONE_STOP_BIT, UART_BaudRate };
	UART_init(&uart_config);
	Timer_ConfigType timer_config = { 0, 7813, TIMER1, NO_CLOCK, COMPARE_MODE };
	Timer_init(&timer_config);
	Timer_setCallBack(timer_callback, TIMER1);

	uint8 password[PASSWORD_LENGTH];
	uint8 verification_password[PASSWORD_LENGTH];
	uint8 result;
	uint8 result2;
	while (1) {
		switch (state) {
		case ENTER_PASSWORD:
			LCD_clearScreen();
			LCD_displayString("Enter Password:");
			LCD_moveCursor(1, 0);
			for (uint8 i = 0; i < PASSWORD_LENGTH; i++) {
				password[i] = KEYPAD_getPressedKey();
				LCD_displayCharacter('*');
			}
			while (KEYPAD_getPressedKey() != ENTER_KEY) {
				// Wait for enter key
			}
			state = RE_ENTER_PASSWORD;
			break;

		case RE_ENTER_PASSWORD:
			LCD_clearScreen();
			LCD_displayString("Re-enter");
			LCD_moveCursor(1, 0);
			LCD_displayString("pass:");
			for (uint8 j = 0; j < PASSWORD_LENGTH; j++) {
				verification_password[j] = KEYPAD_getPressedKey();
				LCD_displayCharacter('*');
			}
			while (KEYPAD_getPressedKey() != ENTER_KEY) {
				// Wait for enter key
			}

			// Send password and verification password to Control ECU with delays
			for (uint8 k = 0; k < PASSWORD_LENGTH; k++) {
				UART_sendByte(password[k]);
				_delay_ms(50);
			}
			for (uint8 k = 0; k < PASSWORD_LENGTH; k++) {
				UART_sendByte(verification_password[k]);
				_delay_ms(50);
			}

			state = WAIT_FOR_CONFIRMATION;
			break;

		case WAIT_FOR_CONFIRMATION:
			result = UART_recieveByte();
			if (result == 1) {
				LCD_clearScreen();
				LCD_displayString("Access Granted!");
				_delay_ms(500);
				state = MAIN_OPTIONS;
			} else {
				LCD_clearScreen();
				LCD_displayString("Password");
				LCD_moveCursor(1, 0);
				LCD_displayString("Mismatch");
				_delay_ms(500);
				state = ENTER_PASSWORD;
			}
			break;

		case MAIN_OPTIONS:
			LCD_clearScreen();
			LCD_displayString("+:Open Door");
			LCD_moveCursor(1, 0);
			LCD_displayString("-:Change Pass");

			uint8 option = KEYPAD_getPressedKey();
			if (option == '+') {
				state = OPEN_DOOR;
			} else if (option == '-') {
				state = CHANGE_PASSWORD;
			}
			break;

		case OPEN_DOOR:
			UART_sendByte(0);
			LCD_clearScreen();
			LCD_displayString("Enter Password:");
			LCD_moveCursor(1, 0);

			for (uint8 q = 0; q < PASSWORD_LENGTH; q++) {
				password[q] = KEYPAD_getPressedKey();
				LCD_displayCharacter('*');
			}

			while (KEYPAD_getPressedKey() != ENTER_KEY) {
				// Wait for enter key
			}

			for (uint8 w = 0; w < PASSWORD_LENGTH; w++) {
				UART_sendByte(password[w]);
				_delay_ms(50);
			}

			result2 = UART_recieveByte();
			_delay_ms(50);
			if (result2 == 1) {
				LCD_clearScreen();
				LCD_displayString("Door Opening    ");
				tick = 0;
				Timer_start(TIMER1, F_CPU_1024);
				while (tick <= DOOR_OPEN_TIME)
					;
				uint8 PIR_status = 1;
				if (PIR_status == 1) {
					LCD_clearScreen();
					LCD_displayString("waiting for ");
					LCD_moveCursor(1, 0);
					LCD_displayString("people");
				}
				while (PIR_status == 1) {
					PIR_status = UART_recieveByte();
					_delay_ms(50);
				}
				tick = 0;
				LCD_clearScreen();
				LCD_displayString("Door closing");
				while (tick <= DOOR_OPEN_TIME)
					;
				attempt_count = 0;
				state = MAIN_OPTIONS;
			} else {
				LCD_clearScreen();
				LCD_displayString("Incorrect Pass");
				_delay_ms(500);

				attempt_count++;
				if (attempt_count == MAX_ATTEMPTS) {
					LCD_clearScreen();
					LCD_displayString("System Locked");
					attempt_count = 0; // Reset attempt count after lockout
					tick = 0;
					Timer_start(TIMER1, F_CPU_1024);
					while (tick <= LOCKOUT_TIME)
						;
					state = MAIN_OPTIONS;

				} else {
					state = OPEN_DOOR; // Retry password entry
				}
			}
			break;

		case CHANGE_PASSWORD:
			UART_sendByte(1);
			LCD_clearScreen();
			LCD_displayString("Enter Old");
			LCD_moveCursor(1, 0);
			LCD_displayString("Password:");
			for (uint8 h = 0; h < PASSWORD_LENGTH; h++) {
				password[h] = KEYPAD_getPressedKey();
				LCD_displayCharacter('*');
			}

			while (KEYPAD_getPressedKey() != ENTER_KEY)
				; // Wait for enter key

			for (uint8 w = 0; w < PASSWORD_LENGTH; w++) {
				UART_sendByte(password[w]);
				_delay_ms(50);
			}

			result2 = UART_recieveByte();
			_delay_ms(50);
			if (result2 == 1) {
				attempt_count = 0;
				state = ENTER_PASSWORD; // Go to new password entry
			} else {
				LCD_clearScreen();
				LCD_displayString("Incorrect Pass");
				_delay_ms(500);

				attempt_count++;
				if (attempt_count >= MAX_ATTEMPTS) {
					LCD_clearScreen();
					LCD_displayString("System Locked");
					attempt_count = 0; // Reset attempt count after lockout
					tick = 0;
					Timer_start(TIMER1, F_CPU_1024);
					while (tick <= LOCKOUT_TIME);
					state = MAIN_OPTIONS;
				} else {
					state = CHANGE_PASSWORD; // Retry password entry for change
				}
			}
			break;
		}
	}
}

void timer_callback() {
	tick++;
}

