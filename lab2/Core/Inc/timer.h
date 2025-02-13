/*
 * timer.h
 *
 *  Created on: Oct 23, 2024
 *  Updated on: Dec 01, 2024
 *  Updated on: Feb 13, 2025
 *      Author: coehl
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_

#include "stm32f1xx_hal.h"

extern TIM_HandleTypeDef htim2; // Increments once approximately every 1ms

/*
 * Returns the current value of the htim1 timer
 */
int32_t timer_start();

/*
 * Returns the difference between the start time and time this function is
 * called. Takes into account 1 roll over.
 */
int32_t timer_stop(int32_t start);

#endif /* INC_TIMER_H_ */
