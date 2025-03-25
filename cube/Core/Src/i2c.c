/*
 * i2c.c
 *
 *  Created on: Mar 24, 2025
 *      Author: coehl
 */

#include "i2c.h"

bool sendI2cDataBlocking(uint8_t *data, uint16_t addr, uint16_t size){
	HAL_StatusTypeDef status = HAL_I2C_Master_Transmit(&hi2c1, addr, data, size, 100);
	if(status == HAL_OK) return true;
	return false;
}

bool recieveI2cDataBlocking(uint8_t *data, uint16_t addr, uint16_t size){
	HAL_StatusTypeDef status = HAL_TIMEOUT;
	while(status == HAL_TIMEOUT){
		status = HAL_I2C_Master_Receive(&hi2c1, addr, data, size, 100);
	}
	if(status == HAL_OK) return true;
	return false;
}
