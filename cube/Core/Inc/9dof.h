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

#define LSM303_ADDRESS_ACCEL          (0x19 << 1)         // 0011001x
#define LSM303_ADDRESS_MAG            (0x1e << 1)         // 0011110x
#define L3GD20_ADDRESS_GYRO           (0x6B << 1)         // 1101011x

#define GYRO_REGISTER_CTRL_REG1       (0x20)
#define GYRO_REGISTER_CTRL_REG4       (0x23)
#define GYRO_REGISTER_OUT_X_L         (0x28)

#define SENSORS_DPS_TO_RADS           (0.017453293F)
#define GYRO_SENSITIVITY_250DPS       (0.00875F)
#define GYRO_SENSITIVITY_500DPS       (0.0175F)
#define GYRO_SENSITIVITY_2000DPS      (0.070F)

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

#endif /* INC_9DOF_H_ */
