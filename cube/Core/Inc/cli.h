/*
 * cli.h
 *
 *  Created on: Oct 8, 2024
 *  Updated on: Feb 13, 2025
 *      Author: coehl
 */

#ifndef INC_CLI_H_
#define INC_CLI_H_

#include "stm32f1xx_hal.h"
#include "cmsis_os2.h"

extern UART_HandleTypeDef huart2;
extern osMessageQueueId_t imuOrientationQueueHandle;

/*
 * Clears the screen, and prints prompt in interrupt mode
 */
void setupCliWithInterrupt();

/*
 * Clears the screen, and prints prompt in non-interrupt mode
 */
void setupCli();

/*
 * Poll serial for single character, store characters entered, and process
 * command on enter.
 */
void pollCli();

#endif /* INC_CLI_H_ */
