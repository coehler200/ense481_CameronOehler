/*
 * imu.h
 *
 *  Created on: Apr 9, 2025
 *      Author: coehl
 */

#ifndef INC_IMU_H_
#define INC_IMU_H_

#include "cmsis_os2.h"

extern osMessageQueueId_t imuOrientationQueueHandle;

void setupImu(void);
void pollImu(void);

#endif /* INC_IMU_H_ */
