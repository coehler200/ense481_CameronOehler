/**
  ******************************************************************************
  * @file     spi.c
  * @brief    Functions to communicate with SPI devices (including ones using SDEP)
  * @author   Cameron Oehler
  ******************************************************************************
  *
  * Includes basic methods for communicating with SPI devices. Also includes a simple
  * ring buffer system for receiving data and methods for sending SPEP (an Adafruit
  * protocol) packets.
  *
  *	Created on: Apr 9, 2025
  *
  ******************************************************************************
  */

#include "spi.h"
#include "cmsis_os2.h"

/** Maximum length of the rx ring buffer */
#define SPI_RX_BUFFER_MAX 128

uint8_t spiRxBuffer[SPI_RX_BUFFER_MAX];
uint8_t spiRxBufferTail = 0;
uint8_t spiRxBufferHead = 0;
uint8_t spiRxBufferLen = 0;

/**
 * Return if the rx ring buffer is empty
 *
 * @return bool indicating if the buffer is empty (true) or not empty (false)
 */
bool isSpiRxBufferEmpty(void){
	return spiRxBufferLen == 0;
}

/**
 * Return if the rx ring buffer is full
 *
 * @return bool indicating if the buffer is full (true) or not full (false)
 */
bool isSpiRxBufferFull(void){
	return spiRxBufferLen >= SPI_RX_BUFFER_MAX;
}

/**
 * Add a byte of data to the head of the ring buffer
 *
 * @param d byte to be added to buffer
 * @return bool indicating if the add command succeeded
 */
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

/**
 * Remove a byte of data from the tail of the ring buffer
 *
 * @return byte removed or defaults to 0 if failed
 */
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

/**
 * Transmit bytes of data over SPI in a blocking mode. Receive data at the
 * same time and put into ring buffer.
 *
 * @param txBuf buffer containing bytes to send
 * @param len length of buffer to be sent
 */
void spiTransmitBlocking(uint8_t *txBuf, uint8_t len){
	uint8_t rxBuf[32];
	HAL_SPI_TransmitReceive(&hspi2, txBuf, (uint8_t *)&rxBuf, len, 1000);
	for(uint8_t i=0; i<len; i++){
		addToSpiRxBuffer(rxBuf[i]);
	}
}

/**
 * Receive bytes of data over SPI in a blocking mode. First tries to pull
 * from ring buffer before reading more data from SPI.
 *
 * @param rxBuf buffer to which bytes read will be stored
 * @param len amount of bytes to receive
 */
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

/**
 * Setup a SDEP packet header
 *
 * @param packet a pointer to the Packet that will have its header set
 * @param commandType the SDEP command type
 * @param commandId the SDEP command id
 * @param payloadLen the length in bytes of the payload (max 16bytes)
 * @param moreData a flag indicating if the payload consists of multiple packets (ie. >16 bytes)
 */
void setupPacketHeader(struct Packet *packet, uint8_t commandType, uint16_t commandId, uint8_t payloadLen, bool moreData){
	packet->commandType = commandType;
	packet->commandId = commandId;
	packet->payloadLen = (moreData ? 0x80|payloadLen : payloadLen); // If moreData set bit 4 (means data across mult packets)
}

/**
 * Send a SDEP Packet over SPI
 *
 * @param packet a pointer to the Packet to be sent
 */
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

/**
 * Receive a SDEP Packet over SPI (blocks until data is available and received data is valid)
 *
 * @param packet a pointer to the Packet where the received data will be stored
 * @return success/failure flag
 */
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
