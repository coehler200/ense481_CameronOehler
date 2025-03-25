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

struct Vec3 {
	uint8_t x;
	uint8_t y;
	uint8_t z;
};

bool setupL3GD20H(void);
bool setupLSM303DLHC(void);

struct Vec3 readGyroscope(void);
struct Vec3 readAccelerometer(void);
struct Vec3 readMag(void);

#endif /* INC_9DOF_H_ */
