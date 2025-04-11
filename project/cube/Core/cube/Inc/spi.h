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

/** SDEP message type of command */
#define SDEP_MSGTYPE_COMMAND                 (uint8_t)(0x10)
/** SDEP message type of response */
#define SDEP_MSGTYPE_RESPONSE                (uint8_t)(0x20)
/** SDEP message type of alert */
#define SDEP_MSGTYPE_ALERT                   (uint8_t)(0x40)
/** SDEP message type of error */
#define SDEP_MSGTYPE_ERROR                   (uint8_t)(0x80)
/** SDEP message type of slave device not ready */
#define SDEP_MSGTYPE_SLAVE_NOT_READY         (uint8_t)(0xFE)
/** SDEP message type of slave device overflow */
#define SDEP_MSGTYPE_SLAVE_OVERFLOW          (uint8_t)(0xFF)

/** SDEP command type of init */
#define SDEP_CMDTYPE_INITIALIZE              (uint16_t)(0xBEEF)
/** SDEP command type of at wrapper */
#define SDEP_CMDTYPE_AT_WRAPPER              (uint16_t)(0x0A00)
/** SDEP command type of ble tx */
#define SDEP_CMDTYPE_BLE_TX                  (uint16_t)(0x0A01)
/** SDEP command type of ble rx */
#define SDEP_CMDTYPE_BLE_RX                  (uint16_t)(0x0A02)

extern SPI_HandleTypeDef hspi2;

/**
 * A SDEP packet
 */
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
