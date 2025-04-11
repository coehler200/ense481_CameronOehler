/*
 * spi.h
 *
 *  Created on: Apr 9, 2025
 *      Author: coehl
 */

#ifndef INC_SPI_H_
#define INC_SPI_H_

#include "stm32f1xx_hal.h"
#include "stdbool.h"

#define SDEP_MSGTYPE_COMMAND                 (uint8_t)(0x10)
#define SDEP_MSGTYPE_RESPONSE                (uint8_t)(0x20)
#define SDEP_MSGTYPE_ALERT                   (uint8_t)(0x40)
#define SDEP_MSGTYPE_ERROR                   (uint8_t)(0x80)
#define SDEP_MSGTYPE_SLAVE_NOT_READY         (uint8_t)(0xFE)
#define SDEP_MSGTYPE_SLAVE_OVERFLOW          (uint8_t)(0xFF)

#define SDEP_CMDTYPE_INITIALIZE              (uint16_t)(0xBEEF)
#define SDEP_CMDTYPE_AT_WRAPPER              (uint16_t)(0x0A00)
#define SDEP_CMDTYPE_BLE_TX                  (uint16_t)(0x0A01)
#define SDEP_CMDTYPE_BLE_RX                  (uint16_t)(0x0A02)

extern SPI_HandleTypeDef hspi2;

struct Packet {
	uint8_t commandType;
	uint16_t commandId;
	uint8_t payloadLen;
	uint8_t payload[16];
};

bool isSpiRxBufferEmpty(void);
bool isSpiRxBufferFull(void);
bool addToSpiRxBuffer(uint8_t d);
uint8_t removeFromSpiRxBuffer(void);

void spiTransmitBlocking(uint8_t *txBuf, uint8_t len);
void spiReceiveBlocking(uint8_t *rxBuf, uint8_t len);
void setupPacketHeader(struct Packet *packet, uint8_t command_type, uint16_t command_id, uint8_t payload_len, bool moreData);
void sendPacket(struct Packet *packet);
bool receivePacket(struct Packet *packet);

#endif /* INC_SPI_H_ */
