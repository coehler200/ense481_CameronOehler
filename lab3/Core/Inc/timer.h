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
 * Configures and starts htim2
 */
void timer_init(void);

/*
 * Returns the current value of the htim1 timer
 */
uint16_t timer_start(void);

/*
 * Returns the difference between the start time and time this function is
 * called. Takes into account 1 roll over.
 */
uint16_t timer_stop(uint16_t start);

/*
 * Release timer and reset it to its default state
 */
void timer_shutdown(void);

#endif /* INC_TIMER_H_ */
