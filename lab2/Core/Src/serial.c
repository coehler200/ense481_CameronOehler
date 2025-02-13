/*
 * serial.c
 *
 *  Created on: Oct 23, 2024
 *  Updated on: Feb 13, 2025
 *      Author: coehl
 */

#include "serial.h"

void serialPrint(char* msg, uint16_t size){
	while((HAL_UART_GetState(&huart2)&HAL_UART_STATE_BUSY_TX)==
			HAL_UART_STATE_BUSY_TX);
	HAL_UART_Transmit_IT(&huart2, (uint8_t*)msg, size);
}

void serialPrintBlocking(char* msg, uint16_t size){
	HAL_UART_Transmit(&huart2, (uint8_t*)msg, size, 100);
}

void receiveChar(char *buf){
	while((HAL_UART_GetState(&huart2)&HAL_UART_STATE_BUSY_RX)==
			HAL_UART_STATE_BUSY_RX);
	HAL_UART_Receive_IT(&huart2, (uint8_t*)buf, 1);
}

char receiveCharBlocking(){
	char c[1];
	HAL_StatusTypeDef status = HAL_TIMEOUT;
	while(status == HAL_TIMEOUT){
		status = HAL_UART_Receive(&huart2, (uint8_t*)c, 1, 100);
	}
	return c[0];
}
