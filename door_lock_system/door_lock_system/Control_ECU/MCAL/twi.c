 /******************************************************************************
 *
 * Module: TWI(I2C)
 *
 * File Name: twi.h
 *
 * Description: Source file for the TWI(I2C) AVR driver
 *
 * Author: Abdelrhman Adel Sakr
 *
 *******************************************************************************/
 
#include "twi.h"
#include "common_macros.h"
#include <avr/io.h>

#define F_CPU 8000000UL  // CPU frquency
TWI_ConfigType I2C_config={.address=MY_ADDRESS,.bit_rate=TWI_BIT_RATE_400KHZ};

void TWI_init(const TWI_ConfigType *config) {
    // Set the bit rate for TWI communication
    TWSR = 0x00; // Clear prescaler bits
    TWBR = (uint8)(((F_CPU / config->bit_rate) - 16) / 2); // Set bit rate register

    // Set the TWI address
    TWAR = (config->address << 1); // Load address into TWAR (shifted left by 1 to fit TWI format)

    // Enable the TWI module
    TWCR = (1 << TWEN);
}

void TWI_start(void)
{
    /* 
	 * Clear the TWINT flag before sending the start bit TWINT=1
	 * send the start bit by TWSTA=1
	 * Enable TWI Module TWEN=1 
	 */
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    
    /* Wait for TWINT flag set in TWCR Register (start bit is send successfully) */
    while(BIT_IS_CLEAR(TWCR,TWINT));
}

void TWI_stop(void)
{
    /* 
	 * Clear the TWINT flag before sending the stop bit TWINT=1
	 * send the stop bit by TWSTO=1
	 * Enable TWI Module TWEN=1 
	 */
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

void TWI_writeByte(uint8 data)
{
    /* Put data On TWI data Register */
    TWDR = data;
    /* 
	 * Clear the TWINT flag before sending the data TWINT=1
	 * Enable TWI Module TWEN=1 
	 */ 
    TWCR = (1 << TWINT) | (1 << TWEN);
    /* Wait for TWINT flag set in TWCR Register(data is send successfully) */
    while(BIT_IS_CLEAR(TWCR,TWINT));
}

uint8 TWI_readByteWithACK(void)
{
	/* 
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable sending ACK after reading or receiving data TWEA=1
	 * Enable TWI Module TWEN=1 
	 */ 
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
    /* Wait for TWINT flag set in TWCR Register (data received successfully) */
    while(BIT_IS_CLEAR(TWCR,TWINT));
    /* Read Data */
    return TWDR;
}

uint8 TWI_readByteWithNACK(void)
{
	/* 
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable TWI Module TWEN=1 
	 */
    TWCR = (1 << TWINT) | (1 << TWEN);
    /* Wait for TWINT flag set in TWCR Register (data received successfully) */
    while(BIT_IS_CLEAR(TWCR,TWINT));
    /* Read Data */
    return TWDR;
}

uint8 TWI_getStatus(void)
{
    uint8 status;
    /* masking to eliminate first 3 bits and get the last 5 bits (status bits) */
    status = TWSR & 0xF8;
    return status;
}
