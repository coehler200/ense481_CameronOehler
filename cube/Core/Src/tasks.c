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
#include "cmsis_os2.h"

// Remove after proper task creation
#include "9dof.h"
#include "serial.h"
#include "string.h"
#include "stdio.h"
// End prev comment

/**
 * Entry point for the task ReadImu
 *
*/
void StartReadImu(void *argument){
	// TODO: Make this a proper task in own file
	if(!setupL3GD20H()){
		for(;;){
			osDelay(1000);
		}
	}
	for(;;){
		struct Vec3 data;
		if(readGyroscope(&data)){
			char buf[64] = "";
			sprintf(buf, "x: %f, y: %f, z: %f\r\n", data.x, data.y, data.z);
			serialPrintBlocking(buf, strlen(buf));
		}
		osDelay(1000);
	}
}

/**
 * Entry point for the task Cli
 *
*/
void StartCli(void *argument){
	setupCli();
	pollCli();
}
