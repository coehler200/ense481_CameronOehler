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

#define LSM303_ADDRESS_ACCEL                 (0x19 << 1)         // 0011001x
#define LSM303_ADDRESS_MAG                   (0x1e << 1)         // 0011110x
#define L3GD20_ADDRESS_GYRO                  (0x6B << 1)         // 1101011x

#define GYRO_REGISTER_CTRL_REG1              (0x20)
#define GYRO_REGISTER_CTRL_REG4              (0x23)
#define GYRO_REGISTER_OUT_X_L                (0x28)

#define LSM303_REGISTER_ACCEL_CTRL_REG1_A    (0x20)
#define LSM303_REGISTER_ACCEL_OUT_X_L_A      (0x28)
#define LSM303ACCEL_MG_LSB                   (0.001F)
#define SENSORS_GRAVITY_STANDARD             (9.80665F)

#define LSM303_REGISTER_MAG_MR_REG_M         (0x02)
#define LSM303_REGISTER_MAG_OUT_X_H_M        (0x03)
#define LSM303MAG_GAUSS_LSB_XY               (1100)
#define LSM303MAG_GAUSS_LSB_Z                (980)
#define SENSORS_GAUSS_TO_MICROTESLA          (100)

#define SENSORS_DPS_TO_RADS                  (0.017453293F)
#define GYRO_SENSITIVITY_250DPS              (0.00875F)
#define GYRO_SENSITIVITY_500DPS              (0.0175F)
#define GYRO_SENSITIVITY_2000DPS             (0.070F)

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
