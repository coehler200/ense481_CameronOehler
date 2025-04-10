/*
 * ble.h
 *
 *  Created on: Apr 9, 2025
 *      Author: coehl
 */

#ifndef INC_BLE_H_
#define INC_BLE_H_

#include "stm32f1xx_hal.h"
#include "stdbool.h"

bool setupBLE(void);
bool sendMessage(uint8_t *data);

#endif /* INC_BLE_H_ */
