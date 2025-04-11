/*
 * 9dof.h
 *
 *  Created on: Mar 24, 2025
 *      Author: coehl
 */

#ifndef INC_9DOF_H_
#define INC_9DOF_H_

#include "stm32f1xx_hal.h"

#include "stdbool.h"

#define PI                                   (3.14159265F)

/** The address of the accelerometer */
#define LSM303_ADDRESS_ACCEL                 (0x19 << 1)         // 0011001x
/** The address of the magnetometer */
#define LSM303_ADDRESS_MAG                   (0x1e << 1)         // 0011110x
/** The address of the gyroscope */
#define L3GD20_ADDRESS_GYRO                  (0x6B << 1)         // 1101011x

/** The address of the gyro CTRL_REG1 register */
#define GYRO_REGISTER_CTRL_REG1              (0x20)
/** The address of the gyro CTRL_REG4 register */
#define GYRO_REGISTER_CTRL_REG4              (0x23)
/** The address of the gyro OUT_X_L register */
#define GYRO_REGISTER_OUT_X_L                (0x28)

/** The address of the accelerometer CTRL_REG1_A register */
#define LSM303_REGISTER_ACCEL_CTRL_REG1_A    (0x20)
/** The address of the accelerometer OUT_X_L_A register */
#define LSM303_REGISTER_ACCEL_OUT_X_L_A      (0x28)
/** A value that all accelerometer readings need to be multiplied by */
#define LSM303ACCEL_MG_LSB                   (0.001F)

/** Gravity of earth (m/s) */
#define SENSORS_GRAVITY_STANDARD             (9.80665F)

/** The address of the magnetometer MR_REG_M register */
#define LSM303_REGISTER_MAG_MR_REG_M         (0x02)
/** The address of the magnetometer OUT_X_H_M register */
#define LSM303_REGISTER_MAG_OUT_X_H_M        (0x03)
/** A value that all x&y magnetometer readings need to be divided by */
#define LSM303MAG_GAUSS_LSB_XY               (1100)
/** A value that all z magnetometer readings need to be divided by */
#define LSM303MAG_GAUSS_LSB_Z                (980)
/** Conversion value between gauss and microtesla */
#define SENSORS_GAUSS_TO_MICROTESLA          (100)

/** Conversion value between dps and rads */
#define SENSORS_DPS_TO_RADS                  (0.017453293F)
/** A value that all gyroscope readings of 250dps need to be multiplied by */
#define GYRO_SENSITIVITY_250DPS              (0.00875F)
/** A value that all gyroscope readings of 500 need to be multiplied by */
#define GYRO_SENSITIVITY_500DPS              (0.0175F)
/** A value that all gyroscope readings of 2000dps need to be multiplied by */
#define GYRO_SENSITIVITY_2000DPS             (0.070F)

/**
 * A container for storing x, y, and z data as floats
 */
struct Vec3 {
	float x;
	float y;
	float z;
};

bool setupL3GD20H(void);
bool setupLSM303DLHC(void);

bool readGyroscope(struct Vec3 *data);
bool readAccelerometer(struct Vec3 *data);
bool readMag(struct Vec3 *data);

bool getOrientation(struct Vec3 *data);

#endif /* INC_9DOF_H_ */
