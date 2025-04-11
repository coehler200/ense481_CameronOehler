/**
  ******************************************************************************
  * @file     i2c.c
  * @brief    Functions to communicate with the I2C system
  * @author   Cameron Oehler
  ******************************************************************************
  *
  * Various helper functions to easily integrate code with I2C
  *
  *	Created on: Mar 24, 2025
  *
  ******************************************************************************
  */

#include "i2c.h"

/**
 * Send data through I2C in a blocking mode
 *
 * @param data a pointer to the data to be sent
 * @param addr the i2c address of the device to transmit to
 * @param size the number of bytes to transmit
 * @return Success flag
 */
bool sendI2cDataBlocking(uint8_t *data, uint16_t addr, uint16_t size){
	HAL_StatusTypeDef status = HAL_I2C_Master_Transmit(&hi2c1, addr, data, size, 1000);
	if(status == HAL_OK) return true;
	return false;
}

/**
 * Receive data through I2C in a blocking mode
 *
 * @param data a pointer to memory where the data can be saved
 * @param addr the i2c address of the device to receive from
 * @param size the number of bytes to receive
 * @return Success flag
 */
bool recieveI2cDataBlocking(uint8_t *data, uint16_t addr, uint16_t size){
	HAL_StatusTypeDef status = HAL_TIMEOUT;
	while(status == HAL_TIMEOUT){
		status = HAL_I2C_Master_Receive(&hi2c1, addr, data, size, 1000);
	}
	if(status == HAL_OK) return true;
	return false;
}

/**
 * Send a single byte through I2C in a blocking mode.
 *
 * @param data a single byte of data to be sent
 * @param addr the i2c address of the device to transmit to
 * @return Success flag
 */
bool sendI2cByteBlocking(uint8_t data, uint16_t addr){
	return sendI2cDataBlocking(&data, addr, 1);
}

/**
 * Send a two bytes, a register and data, through I2C in a blocking mode
 *
 * @param reg the register of the i2c device to manipulate
 * @param data the date to write to the i2c device at the register location
 * @param addr the i2c address of the device to transmit to
 * @return Success flag
 */
bool sendI2cCmdBlocking(uint8_t reg, uint8_t data, uint16_t addr){
	uint8_t buf[2] = {reg, data};
	return sendI2cDataBlocking(buf, addr, 2);
}

/**
 * Receive a single byte through I2C in a blocking mode
 *
 * @param addr the i2c address of the device to receive from
 * @return Byte received (or '0' if error)
 */
uint8_t recieveI2cByteBlocking(uint16_t addr){
	uint8_t data[1];
	bool success = recieveI2cDataBlocking(data, addr, 1);
	if(success) return data[0];
	return 0; // If some sort of error, return a 0x0
}
