/**
  ******************************************************************************
  * @file     ble.c
  * @brief    Communicate with the Adafruit Bluefruit SPI board
  * @author   Cameron Oehler
  ******************************************************************************
  *
  * Uses paraphrased information/code from the Adafruit BLE (and related) libraries
  *
  *	Created on: Apr  9, 2025
  *	Updated on: Apr  10, 2025
  *
  ******************************************************************************
  */

#include "ble.h"
#include "spi.h"
#include "cmsis_os2.h"

/**
 * Reset BLE device via hardware reset and wait for reboot
 */
void setupBLE(void){
	osDelay(100);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET);
	osDelay(500);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_SET);
	osDelay(1000);
}

/**
 * Read data from BLE until data is no longer available
 */
void flush(void){
	while(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_3)){ // Pin is high when data is available
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_RESET); // CS low
		osDelay(100);
		uint8_t data[64];
		receiveMessage((uint8_t *)&data); // Receive a message of up to 64 bytes (design limitation)
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_SET); // CS high
		osDelay(100);
	}
}

/**
 * Send a message over the BLE device
 *
 * @param data pointer to a data buffer containing the message to send
 * @param dataLen length of the data in the data buffer to be sent
 * @return bool indicating success or failure
 */
bool sendMessage(uint8_t *data, uint16_t dataLen){
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_RESET);
	osDelay(100);
	uint16_t remainingPayload = dataLen;
	uint16_t payloadIndex = 0;
	while(remainingPayload > 0){
		uint8_t currentPayloadLen = (remainingPayload > 16) ? 16 : remainingPayload;
		bool moreData = (remainingPayload > 16) ? true : false;

		struct Packet p;
		setupPacketHeader(&p, SDEP_MSGTYPE_COMMAND, SDEP_CMDTYPE_BLE_TX, currentPayloadLen, moreData);

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

/**
 * Receive a message over the BLE device
 *
 * @param data pointer to a data buffer where the message will be stored
 * @return uint16_t containing the total message length
 */
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
