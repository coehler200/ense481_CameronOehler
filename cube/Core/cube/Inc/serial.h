/*
 * serial.h
 *
 *  Created on: Oct 23, 2024
 *  Updated on: Feb 13, 2025
 *      Author: coehl
 */

#ifndef INC_SERIAL_H_
#define INC_SERIAL_H_

#include "stm32f1xx_hal.h"

extern UART_HandleTypeDef huart2;

/*
 * Print the msg to huart2 in interrupt mode
 */
void serialPrint(char* msg, uint16_t size);

/*
 * Print the msg to huart2 in blocking mode
 */
void serialPrintBlocking(char* msg, uint16_t size);

/*
 * Receive a single char from huart2 in interrupt mode and store to buf
 */
void receiveChar(char *buf);

/*
 * Receive a single char from huart2 in blocking mode and return
 */
char receiveCharBlocking();

#endif /* INC_SERIAL_H_ */
