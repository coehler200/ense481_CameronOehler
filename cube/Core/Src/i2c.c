/*
 * i2c.c
 *
 *  Created on: Mar 24, 2025
 *      Author: coehl
 */

#include "i2c.h"

bool sendI2cDataBlocking(uint8_t *data, uint16_t addr, uint16_t size){
	HAL_StatusTypeDef status = HAL_I2C_Master_Transmit(&hi2c1, addr, data, size, 1000);
	if(status == HAL_OK) return true;
	return false;
}

bool recieveI2cDataBlocking(uint8_t *data, uint16_t addr, uint16_t size){
	HAL_StatusTypeDef status = HAL_TIMEOUT;
	while(status == HAL_TIMEOUT){
		status = HAL_I2C_Master_Receive(&hi2c1, addr, data, size, 1000);
	}
	if(status == HAL_OK) return true;
	return false;
}

bool sendI2cByteBlocking(uint8_t data, uint16_t addr){
	return sendI2cDataBlocking(&data, addr, 1);
}

bool sendI2cCmdBlocking(uint8_t reg, uint8_t data, uint16_t addr){
	uint8_t buf[2] = {reg, data};
	return sendI2cDataBlocking(buf, addr, 2);
}

uint8_t recieveI2cByteBlocking(uint16_t addr){
	uint8_t data[1];
	bool success = recieveI2cDataBlocking(data, addr, 1);
	if(success) return data[0];
	return 0; // If some sort of error, return a 0x0
}
