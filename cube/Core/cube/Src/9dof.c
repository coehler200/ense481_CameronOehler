/**
  ******************************************************************************
  * @file     9dof.c
  * @brief    Communicate with the Adafruit 9DOF board
  * @author   Cameron Oehler
  ******************************************************************************
  *
  * Uses paraphrased information/code from the Adafruit 9dof, L3GD20H, and LSM303DLHC
  * libraries
  *
  *	Created on: Mar 24, 2025
  *	Updated on: Apr  9, 2025
  *
  ******************************************************************************
  */

#include "9dof.h"
#include "i2c.h"
#include <math.h>

/**
 * Method to setup/configure the L3GD20H device on the 9DOF board
 *
 * @return bool indicating success or failure
 */
bool setupL3GD20H(void){
	bool success = sendI2cCmdBlocking(GYRO_REGISTER_CTRL_REG1, 0x00, L3GD20_ADDRESS_GYRO);
	if(!success) return false;

	success = sendI2cCmdBlocking(GYRO_REGISTER_CTRL_REG1, 0x0F, L3GD20_ADDRESS_GYRO);
	if(!success) return false;

	// Set resolution/gain

	// 250 DPS
	//success = sendI2cCmdBlocking(GYRO_REGISTER_CTRL_REG4, 0x00, L3GD20_ADDRESS_GYRO);

	// 500 DPS
	//success = sendI2cCmdBlocking(GYRO_REGISTER_CTRL_REG4, 0x10, L3GD20_ADDRESS_GYRO);

	// 200 DPS
	success = sendI2cCmdBlocking(GYRO_REGISTER_CTRL_REG4, 0x20, L3GD20_ADDRESS_GYRO);

	if(!success) return false;

	return true;
}

/**
 * Method to setup/configure the LSM303DLHC device on the 9DOF board
 *
 * @return bool indicating success or failure
 */
bool setupLSM303DLHC(void){
	bool success = sendI2cCmdBlocking(LSM303_REGISTER_ACCEL_CTRL_REG1_A, 0x57, LSM303_ADDRESS_ACCEL);
	if(!success) return false;

	success = sendI2cCmdBlocking(LSM303_REGISTER_MAG_MR_REG_M, 0x00, LSM303_ADDRESS_MAG);
	if(!success) return false;

	return true;
}

/**
 * Read data from the gyroscope in rad/s
 *
 * @param data pointer to a Vec3 where the gyroscope data will be stored
 * @return bool indicating success or failure
 */
bool readGyroscope(struct Vec3 *data){
	bool success = sendI2cByteBlocking(GYRO_REGISTER_OUT_X_L | 0x80, L3GD20_ADDRESS_GYRO);
	if(!success) return false;

	uint8_t rawData[6];
	success = recieveI2cDataBlocking(rawData, L3GD20_ADDRESS_GYRO, 6);
	if(!success) return false;

	data->x = ((int16_t)rawData[0] | ((int16_t)rawData[1] << 8));
	data->y = ((int16_t)rawData[2] | ((int16_t)rawData[3] << 8));
	data->z = ((int16_t)rawData[4] | ((int16_t)rawData[5] << 8));

	// Set resolution/gain

//	data->x *= GYRO_SENSITIVITY_250DPS;
//	data->y *= GYRO_SENSITIVITY_250DPS;
//	data->z *= GYRO_SENSITIVITY_250DPS;

//	data->x *= GYRO_SENSITIVITY_500DPS;
//	data->y *= GYRO_SENSITIVITY_500DPS;
//	data->z *= GYRO_SENSITIVITY_500DPS;

	data->x *= GYRO_SENSITIVITY_2000DPS;
	data->y *= GYRO_SENSITIVITY_2000DPS;
	data->z *= GYRO_SENSITIVITY_2000DPS;

	data->x *= SENSORS_DPS_TO_RADS;
	data->y *= SENSORS_DPS_TO_RADS;
	data->z *= SENSORS_DPS_TO_RADS;

	return true;
}

/**
 * Read data from the accelerometer in m/s
 *
 * @param data pointer to a Vec3 where the accelerometer data will be stored
 * @return bool indicating success or failure
 */
bool readAccelerometer(struct Vec3 *data){
	bool success = sendI2cByteBlocking(LSM303_REGISTER_ACCEL_OUT_X_L_A | 0x80, LSM303_ADDRESS_ACCEL);
	if(!success) return false;

	uint8_t rawData[6];
	success = recieveI2cDataBlocking(rawData, LSM303_ADDRESS_ACCEL, 6);
	if(!success) return false;

	data->x = (int16_t)(rawData[0] | (rawData[1] << 8)) >> 4;
	data->y = (int16_t)(rawData[2] | (rawData[3] << 8)) >> 4;
	data->z = (int16_t)(rawData[4] | (rawData[5] << 8)) >> 4;

	data->x *= LSM303ACCEL_MG_LSB * SENSORS_GRAVITY_STANDARD;
	data->y *= LSM303ACCEL_MG_LSB * SENSORS_GRAVITY_STANDARD;
	data->z *= LSM303ACCEL_MG_LSB * SENSORS_GRAVITY_STANDARD;

	return true;
}

/**
 * Read data from the magnetism sensor in microteslas
 *
 * @param data pointer to a Vec3 where the magnetometer data will be stored
 * @return bool indicating success or failure
 */
bool readMag(struct Vec3 *data){
	bool success = sendI2cByteBlocking(LSM303_REGISTER_MAG_OUT_X_H_M, LSM303_ADDRESS_MAG);
	if(!success) return false;

	uint8_t rawData[6];
	success = recieveI2cDataBlocking(rawData, LSM303_ADDRESS_MAG, 6);
	if(!success) return false;

	data->x = (int16_t)((int16_t)rawData[1] | ((int16_t)rawData[0] << 8));
	data->y = (int16_t)((int16_t)rawData[5] | ((int16_t)rawData[4] << 8));
	data->z = (int16_t)((int16_t)rawData[3] | ((int16_t)rawData[2] << 8));

	data->x /= LSM303MAG_GAUSS_LSB_XY * SENSORS_GAUSS_TO_MICROTESLA;
	data->y /= LSM303MAG_GAUSS_LSB_XY * SENSORS_GAUSS_TO_MICROTESLA;
	data->z /= LSM303MAG_GAUSS_LSB_Z * SENSORS_GAUSS_TO_MICROTESLA;

	return true;
}

/**
 * Calculate roll, pitch, and heading by using data from accelerometer and magnetometer
 *
 * @param data pointer to a Vec3 where the calculated orientation data will be stored x(roll), y(pitch), z(heading)
 * @return bool indicating success or failure
 */
bool getOrientation(struct Vec3 *data){
	struct Vec3 accel_data;
	struct Vec3 mag_data;

	if(!readAccelerometer(&accel_data)){
		return false;
	}

	if(!readMag(&mag_data)){
		return false;
	}

	// roll
	data->x = (float)atan2(accel_data.y, accel_data.z);

	// pitch
	if(accel_data.y * sin(data->x) + accel_data.z * cos(data->x) == 0){
		data->y = accel_data.x > 0 ? (PI / 2) : (-PI / 2);
	}
	else{
		data->y = (float)atan(-accel_data.x / (accel_data.y * sin(data->x) + accel_data.z * cos(data->x)));
	}

	// heading
	data->z = (float)atan2(mag_data.z * sin(data->x) - mag_data.y * cos(data->x),
			mag_data.x * cos(data->y) + mag_data.y * sin(data->y) * sin(data->x) +
			mag_data.z * sin(data->y) * cos(data->x));

	// convert to degrees
	data->x *= (180/PI);
	data->y *= (180/PI);
	data->z *= (180/PI);

	return true;
}
