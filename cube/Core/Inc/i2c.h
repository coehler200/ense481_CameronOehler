/*
 * i2c.h
 *
 *  Created on: Mar 24, 2025
 *      Author: coehl
 */

#ifndef INC_I2C_H_
#define INC_I2C_H_

#include "stm32f1xx_hal.h"
#include "stdbool.h"

extern I2C_HandleTypeDef hi2c1;

bool sendI2cDataBlocking(uint8_t *data, uint16_t addr, uint16_t size);
bool recieveI2cDataBlocking(uint8_t *data, uint16_t addr, uint16_t size);

bool sendI2cByteBlocking(uint8_t data, uint16_t addr);
bool sendI2cCmdBlocking(uint8_t reg, uint8_t data, uint16_t addr);
uint8_t recieveI2cByteBlocking(uint16_t addr);

#endif /* INC_I2C_H_ */
