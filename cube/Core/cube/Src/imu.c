/**
  ******************************************************************************
  * @file     imu.c
  * @brief    Functions to be called by a task to setup and poll the IMU
  * @author   Cameron Oehler
  ******************************************************************************
  *
  *	Created on: Apr 9, 2025
  *
  ******************************************************************************
  */

#include "imu.h"
#include "9dof.h"

/**
 * Setup the IMU
 */
void setupImu(){
	if(!setupL3GD20H()){
		for(;;){
			osDelay(1000);
		}
	}
	if(!setupLSM303DLHC()){
		for(;;){
			osDelay(1000);
		}
	}
}

/**
 * Continuously poll the IMU for orientation data and put it into the queue
 */
void pollImu(){
	setupImu();
	for(;;){
		if(osMessageQueueGetSpace(imuOrientationQueueHandle) >= 3){
			struct Vec3 data;
			if(getOrientation(&data)){
				float buf;
				buf = data.x;
				osMessageQueuePut(imuOrientationQueueHandle, &buf, 0, osWaitForever);
				buf = data.y;
				osMessageQueuePut(imuOrientationQueueHandle, &buf, 0, osWaitForever);
				buf = data.z;
				osMessageQueuePut(imuOrientationQueueHandle, &buf, 0, osWaitForever);
			}
		}
		osDelay(50);
	}
}
