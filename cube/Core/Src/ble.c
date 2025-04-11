/*
 * ble.c
 *
 *  Created on: Apr 9, 2025
 *      Author: coehl
 */

#include "ble.h"
#include "spi.h"
#include "cmsis_os2.h"

void setupBLE(void){
	osDelay(100);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET);
	osDelay(500);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_SET);
	osDelay(1000);
}

void flush(void){
	while(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_3)){
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_RESET);
		osDelay(100);
		uint8_t data[64];
		receiveMessage((uint8_t *)&data);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_SET);
		osDelay(100);
	}
}

bool sendMessage(uint8_t *data, uint16_t dataLen){
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_RESET);
	osDelay(100);
	uint16_t remainingPayload = dataLen;
	uint16_t payloadIndex = 0;
	while(remainingPayload > 0){
		uint8_t currentPayloadLen = (remainingPayload > 16) ? 16 : remainingPayload;
		bool moreData = (remainingPayload > 16) ? true : false;

		struct Packet p;
		setupPacketHeader(&p, SDEP_MSGTYPE_COMMAND, SDEP_CMDTYPE_AT_WRAPPER, currentPayloadLen, moreData);

		for(uint16_t i = 0; i<currentPayloadLen; i++){
			p.payload[i] = data[payloadIndex];
			payloadIndex++;
		}

		sendPacket(&p);

		remainingPayload -= currentPayloadLen;

		osDelay(100);
	}
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_SET);

	osDelay(100);

	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_RESET);
	osDelay(100);
	struct Packet rxPacket;
	bool status = receivePacket(&rxPacket);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_SET);

	return status;
}

uint16_t receiveMessage(uint8_t *data){
	uint16_t payloadIndex = 0;
	bool allDataReceived = false;

	if(!HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_3)){
		return 0;
	}

	while(!allDataReceived){
		struct Packet rx;
		bool status = receivePacket(&rx);
		if(!status) return 0;

		if(!(rx.payloadLen&0x80)){
			allDataReceived = true;
		}

		uint8_t payloadLen = rx.payloadLen&0x0F;

		for(uint8_t i=0; i<payloadLen; i++){
			data[payloadIndex] = rx.payload[i];
			payloadIndex++;
		}
	}

	return payloadIndex;
}
