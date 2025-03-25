/*
 * 9dof.c
 *
 *  Created on: Mar 24, 2025
 *      Author: coehl
 */

#include "9dof.h"

#include "i2c.h"

bool setupL3GD20H(void){
	bool success = sendI2cCmdBlocking(0x20, 0x00, L3GD20_ADDRESS_GYRO); // GYRO_REGISTER_CTRL_REG1
	if(!success) return false;
	success = sendI2cCmdBlocking(0x20, 0x0F, L3GD20_ADDRESS_GYRO); // GYRO_REGISTER_CTRL_REG1
	if(!success) return false;

	return true;
}

bool setupLSM303DLHC(void){
	bool success = sendI2cCmdBlocking(0x20, 0x57, LSM303_ADDRESS_ACCEL); // LSM303_REGISTER_ACCEL_CTRL_REG1_A
	if(!success) return false;

	success = sendI2cCmdBlocking(0x02, 0x00, LSM303_ADDRESS_MAG); // LSM303_REGISTER_MAG_MR_REG_M
	if(!success) return false;

	return true;
}

struct Vec3 readGyroscope(void){
	struct Vec3 data;
		data.x = 0;
		data.y = 0;
		data.z = 0;

		bool success = sendI2cByteBlocking(0x28 | 0x80, L3GD20_ADDRESS_GYRO); // GYRO_REGISTER_OUT_X_L | 0x80
		if(!success) return data;

		uint8_t rawData[6];
		success = recieveI2cDataBlocking(rawData, L3GD20_ADDRESS_GYRO, 6);
		if(!success) return data;

		data.x = (int16_t)(rawData[0] | ((int16_t)rawData[1] << 8));
		data.y = (int16_t)(rawData[2] | ((int16_t)rawData[3] << 8));
		data.z = (int16_t)(rawData[4] | ((int16_t)rawData[5] << 8));

		return data;
}

struct Vec3 readAccelerometer(void){
	struct Vec3 data;
	data.x = 0;
	data.y = 0;
	data.z = 0;

	bool success = sendI2cByteBlocking(0x28 | 0x80, LSM303_ADDRESS_ACCEL); // LSM303_REGISTER_ACCEL_OUT_X_L_A | 0x80
	if(!success) return data;

	uint8_t rawData[6];
	success = recieveI2cDataBlocking(rawData, LSM303_ADDRESS_ACCEL, 6);
	if(!success) return data;

	data.x = (int16_t)(rawData[0] | (rawData[1] << 8)) >> 4;
	data.y = (int16_t)(rawData[2] | (rawData[3] << 8)) >> 4;
	data.z = (int16_t)(rawData[4] | (rawData[5] << 8)) >> 4;

	return data;
}

struct Vec3 readMag(void){
	struct Vec3 data;
	data.x = 0;
	data.y = 0;
	data.z = 0;

	bool success = sendI2cByteBlocking(0x03, LSM303_ADDRESS_MAG); // LSM303_REGISTER_MAG_OUT_X_H_M
	if(!success) return data;

	uint8_t rawData[6];
	success = recieveI2cDataBlocking(rawData, LSM303_ADDRESS_MAG, 6);
	if(!success) return data;

	data.x = (int16_t)(rawData[1] | ((int16_t)rawData[0] << 8));
	data.y = (int16_t)(rawData[3] | ((int16_t)rawData[2] << 8));
	data.z = (int16_t)(rawData[5] | ((int16_t)rawData[4] << 8));

	return data;
}
