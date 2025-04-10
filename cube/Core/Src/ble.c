/*
 * ble.c
 *
 *  Created on: Apr 9, 2025
 *      Author: coehl
 */

#include "ble.h"
#include "spi.h"
#include "cmsis_os2.h"

bool setupBLE(void){
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_RESET);
	osDelay(100);
	struct Packet setupPacket;
	setupPacketHeader(&setupPacket, SDEP_MSGTYPE_COMMAND, SDEP_CMDTYPE_INITIALIZE, 0, false);
	sendPacket(&setupPacket);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_SET);

	osDelay(100);

	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_RESET);
	osDelay(100);
	struct Packet rxPacket;
	bool status = receivePacket(&rxPacket);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_SET);

	return status;
}

bool sendMessage(uint8_t *data){
	return true;
}
