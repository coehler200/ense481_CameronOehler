/*
 * timer.c
 *
 *  Created on: Oct 23, 2024
 *  Updated on: Dec 01, 2024
 *      Author: coehl
 */

#include "timer.h"

const int32_t TIMER_MAX = 65535;

void timer_init(){
	HAL_TIM_Base_Start_IT(&htim2);
}

int32_t timer_start(){
	return __HAL_TIM_GET_COUNTER(&htim2);
}

int32_t timer_stop(int32_t start){
	int32_t stop = __HAL_TIM_GET_COUNTER(&htim2);
	if(start > stop){
		start -= TIMER_MAX;
	}
	return stop - start;
}
