/*
 * spi.c
 *
 *  Created on: Apr 9, 2025
 *      Author: coehl
 */

#include "spi.h"

void spiTransmitBlocking(uint8_t *txBuf, uint16_t len){
	HAL_SPI_Transmit(&hspi2, txBuf, len, 1000);
}

void spiReceiveBlocking(uint8_t *rxBuf, uint16_t len){
	HAL_SPI_Receive(&hspi2, rxBuf, len, 1000);
}

void setupPacketHeader(struct Packet *packet, uint8_t commandType, uint16_t commandId, uint8_t payloadLen, bool moreData){
	packet->commandType = commandType;
	packet->commandId = commandId;
	packet->payloadLen = (moreData ? 0x1000|payloadLen : payloadLen); // If moreData set bit 4 (means data across mult packets)
}

void sendPacket(struct Packet *packet){
	uint8_t txBuf[20];
	txBuf[0] = packet->commandType;
	txBuf[1] = packet->commandId&0x00FF; // LSB
	txBuf[2] = (packet->commandId&0xFF00)>>8;
	txBuf[3] = packet->payloadLen;

	uint8_t payloadLen = packet->payloadLen&0x00FF;

	for(uint8_t i = 0; i < payloadLen; i++){
		txBuf[4+i] = packet->payload[i];
	}

	spiTransmitBlocking(txBuf, payloadLen+4);
}

bool receivePacket(struct Packet *packet){
	if(!HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_3)){
		return false;
	}

	uint8_t rxHeaderBuf[4];

	spiReceiveBlocking(rxHeaderBuf, 4);

	packet->commandType = rxHeaderBuf[0];
	packet->commandId = ((uint16_t)rxHeaderBuf[2] << 8) | rxHeaderBuf[1];
	packet->payloadLen = rxHeaderBuf[3];

	uint8_t payloadLen = packet->payloadLen&0x00FF;

	if(payloadLen > 0){
		spiReceiveBlocking(packet->payload, payloadLen);
	}

	return true;
}
