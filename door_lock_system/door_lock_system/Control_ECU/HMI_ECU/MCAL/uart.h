 /******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.h
 *
 * Description: Header file for the UART AVR driver
 *
 * Author: Abdelrhman Adel Sakr
 *
 *******************************************************************************/

#ifndef UART_H_
#define UART_H_

#include "std_types.h"
#define UART_BaudRate 9600
typedef enum {
    UART_ONE_STOP_BIT, UART_TWO_STOP_BITS
} UART_StopBitType;
typedef enum{
	UART_Parity_disable,
	UART_Parity_Even=2,
	UART_Parity_Odd=3
}UART_Parity_Mode;
typedef enum{
	UART_5Bit,UART_6Bit,UART_7Bit,UART_8Bit,UART_9Bit=7
}UART_DataSize;
typedef struct{
	UART_DataSize UART_BitDateType;
	UART_Parity_Mode UART_ParityType;
	UART_StopBitType UART_StopBitType;
	uint32 BaudRateType;
}UART_ConfigType;

//extern UART_ConfigType config_uart;
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init(UART_ConfigType *config);

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data);

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void);

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str);

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str); // Receive until #

#endif /* UART_H_ */
