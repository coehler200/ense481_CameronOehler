/**
  ******************************************************************************
  * @file     serial.c
  * @brief    Functions to communicate with the USART system
  * @author   Cameron Oehler
  ******************************************************************************
  *
  * Various helper functions to easily integrate code with USART
  *
  * Created on: Oct 23, 2024
  * Updated on: Feb 13, 2025
  *
  ******************************************************************************
  */

#include "serial.h"

/**
 * Print data to the usart in a non-blocking (interrupt) mode
 *
 * @param msg a pointer to message to be transmitted
 * @param size the size (in bytes) of the message
 */
void serialPrint(char* msg, uint16_t size){
	while((HAL_UART_GetState(&huart2)&HAL_UART_STATE_BUSY_TX)==
			HAL_UART_STATE_BUSY_TX);
	HAL_UART_Transmit_IT(&huart2, (uint8_t*)msg, size);
}

/**
 * Print data to the usart in a blocking mode
 *
 * @param msg a pointer to message to be transmitted
 * @param size the size (in bytes) of the message
 */
void serialPrintBlocking(char* msg, uint16_t size){
	HAL_UART_Transmit(&huart2, (uint8_t*)msg, size, 100);
}

/**
 * Receive a single char from the usart in a non-blocking (interrupt) mode
 *
 * @param buf the buffer to store the received byte in
 */
void receiveChar(char *buf){
	while((HAL_UART_GetState(&huart2)&HAL_UART_STATE_BUSY_RX)==
			HAL_UART_STATE_BUSY_RX);
	HAL_UART_Receive_IT(&huart2, (uint8_t*)buf, 1);
}

/**
 * Receive a single char from the usart in a blocking mode
 *
 * @return the char received
 */
char receiveCharBlocking(){
	char c[1];
	HAL_StatusTypeDef status = HAL_TIMEOUT;
	while(status == HAL_TIMEOUT){
		status = HAL_UART_Receive(&huart2, (uint8_t*)c, 1, 100);
	}
	return c[0];
}
