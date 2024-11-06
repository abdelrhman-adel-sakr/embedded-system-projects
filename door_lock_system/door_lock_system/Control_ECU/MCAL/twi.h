 /******************************************************************************
 *
 * Module: TWI(I2C)
 *
 * File Name: twi.h
 *
 * Description: Header file for the TWI(I2C) AVR driver
 *
 * Author: Abdelrhman Adel Sakr
 *
 *******************************************************************************/ 

#ifndef TWI_H_
#define TWI_H_

#include "std_types.h"

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/

/* I2C Status Bits in the TWSR Register */
#define TWI_START         0x08 /* start has been sent */
#define TWI_REP_START     0x10 /* repeated start */
#define TWI_MT_SLA_W_ACK  0x18 /* Master transmit ( slave address + Write request ) to slave + ACK received from slave. */
#define TWI_MT_SLA_R_ACK  0x40 /* Master transmit ( slave address + Read request ) to slave + ACK received from slave. */
#define TWI_MT_DATA_ACK   0x28 /* Master transmit data and ACK has been received from Slave. */
#define TWI_MR_DATA_ACK   0x50 /* Master received data and send ACK to slave. */
#define TWI_MR_DATA_NACK  0x58 /* Master received data but doesn't send ACK to slave. */
#define MY_ADDRESS 0b00000010  /* my adress*/

// Enumeration for possible TWI bit rates
typedef enum {
    TWI_BIT_RATE_100KHZ = 100000,
    TWI_BIT_RATE_400KHZ = 400000
} TWI_BaudRateType;

// Enumeration for TWI address
typedef uint8 TWI_AddressType;

// Configuration structure for TWI
typedef struct {
    TWI_AddressType address;
    TWI_BaudRateType bit_rate;
} TWI_ConfigType;
extern TWI_ConfigType I2C_config ;
// Function prototypes
void TWI_init(const TWI_ConfigType *config);
void TWI_start(void);
void TWI_stop(void);
void TWI_writeByte(uint8 data);
uint8 TWI_readByteAck(void);
uint8 TWI_readByteNack(void);
uint8 TWI_getStatus(void);

#endif /* TWI_H_ */
