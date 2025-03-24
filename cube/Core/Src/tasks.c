/*
 * tasks.c
 *
 *  Created on: Mar 23, 2025
 *      Author: coehl
 */

#include "tasks.h"
#include "cli.h"
#include "cmsis_os2.h"

void StartReadImu(void *argument){
	for(;;){
		osDelay(5000);
	}
}

void StartCli(void *argument){
	setupCli();
	pollCli();
}
