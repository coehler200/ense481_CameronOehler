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
	setupL3GD20H();
	for(;;){
		struct Vec3 data = readGyroscope();
		char buf[64] = "";
		sprintf(buf, "x: %i, y: %i, z: %i\r\n", data.x, data.y, data.z);
		serialPrintBlocking(buf, strlen(buf));
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
