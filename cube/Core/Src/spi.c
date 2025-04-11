/*
 * spi.c
 *
 *  Created on: Apr 9, 2025
 *      Author: coehl
 */

#include "spi.h"
#include "cmsis_os2.h"

#define SPI_RX_BUFFER_MAX 128

uint8_t spiRxBuffer[SPI_RX_BUFFER_MAX];
uint8_t spiRxBufferTail = 0;
uint8_t spiRxBufferHead = 0;
uint8_t spiRxBufferLen = 0;

bool isSpiRxBufferEmpty(void){
	return spiRxBufferLen == 0;
}

bool isSpiRxBufferFull(void){
	return spiRxBufferLen >= SPI_RX_BUFFER_MAX;
}

bool addToSpiRxBuffer(uint8_t d){
	if(isSpiRxBufferFull()) return false;

	spiRxBuffer[spiRxBufferHead] = d;

	spiRxBufferHead++;
	spiRxBufferLen++;

	if(spiRxBufferHead >= SPI_RX_BUFFER_MAX){
		spiRxBufferHead = 0;
	}

	return true;
}

uint8_t removeFromSpiRxBuffer(void){
	if(isSpiRxBufferEmpty()) return 0;

	uint8_t d = spiRxBuffer[spiRxBufferTail];

	spiRxBufferTail++;
	spiRxBufferLen--;

	if(spiRxBufferTail >= SPI_RX_BUFFER_MAX){
		spiRxBufferTail = 0;
	}

	return d;
}

void spiTransmitBlocking(uint8_t *txBuf, uint8_t len){
	uint8_t rxBuf[32];
	HAL_SPI_TransmitReceive(&hspi2, txBuf, (uint8_t *)&rxBuf, len, 1000);
	for(uint8_t i=0; i<len; i++){
		addToSpiRxBuffer(rxBuf[i]);
	}
}

void spiReceiveBlocking(uint8_t *rxBuf, uint8_t len){
	uint8_t bufIndex = 0;
	while(!isSpiRxBufferEmpty() && len > 0){
		rxBuf[bufIndex] = removeFromSpiRxBuffer();
		bufIndex++;
		len--;
	}

	if(len > 0){
		uint8_t tempRxBuf[32];
		HAL_SPI_Receive(&hspi2, (uint8_t *)&tempRxBuf, len, 1000);

		for(uint8_t i=0; i<len; i++){
			rxBuf[bufIndex+i] = tempRxBuf[i];
		}
	}
}

void setupPacketHeader(struct Packet *packet, uint8_t commandType, uint16_t commandId, uint8_t payloadLen, bool moreData){
	packet->commandType = commandType;
	packet->commandId = commandId;
	packet->payloadLen = (moreData ? 0x80|payloadLen : payloadLen); // If moreData set bit 4 (means data across mult packets)
}

void sendPacket(struct Packet *packet){
	uint8_t txBuf[20];
	txBuf[0] = packet->commandType;
	txBuf[1] = packet->commandId&0x00FF;
	txBuf[2] = (packet->commandId&0xFF00)>>8;
	txBuf[3] = packet->payloadLen;

	uint8_t payloadLen = packet->payloadLen&0x0F;

	for(uint8_t i = 0; i < payloadLen; i++){
		txBuf[4+i] = packet->payload[i];
	}

	spiTransmitBlocking(txBuf, payloadLen+4);
}

bool receivePacket(struct Packet *packet){
	while(!HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_3)){
		osDelay(100);
	}

	uint8_t rxHeaderBuf[3];
	bool validPacket = false;

	while(!validPacket){
		spiReceiveBlocking(rxHeaderBuf, 1);
		if(rxHeaderBuf[0] == SDEP_MSGTYPE_COMMAND || rxHeaderBuf[0] == SDEP_MSGTYPE_RESPONSE ||
			rxHeaderBuf[0] == SDEP_MSGTYPE_ALERT || rxHeaderBuf[0] == SDEP_MSGTYPE_ERROR){
			validPacket = true;
		}
		else{
			osDelay(1000);
		}
	}

	packet->commandType = rxHeaderBuf[0];

	spiReceiveBlocking(rxHeaderBuf, 3);

	packet->commandId = ((uint16_t)rxHeaderBuf[1] << 8) | rxHeaderBuf[0];
	packet->payloadLen = rxHeaderBuf[2];

	uint8_t payloadLen = packet->payloadLen&0x0F;

	if(payloadLen > 0){
		spiReceiveBlocking(packet->payload, payloadLen);
	}

	return true;
}
