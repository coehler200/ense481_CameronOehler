/**
  ******************************************************************************
  * @file     tasks.c
  * @brief    Provides the entry point for tasks in the system
  * @author   Cameron Oehler
  ******************************************************************************
  *
  *	Created on: Mar 23, 2025
  *
  ******************************************************************************
  */

#include "tasks.h"
#include "cli.h"
#include "imu.h"
#include "ble.h"

/**
 * Entry point for the task ReadImu
 *
*/
void StartReadImu(void *argument){
	pollImu();
}

/**
 * Entry point for the task Cli
 *
*/
void StartCli(void *argument){
	//setupCli();
	//pollCli();
	setupBLE();
}
