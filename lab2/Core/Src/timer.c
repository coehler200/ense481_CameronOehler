/*
 * timer.c
 *
 *  Created on: Oct 23, 2024
 *  Updated on: Dec 01, 2024
 *  Updated on: Feb 13, 2025
 *      Author: coehl
 */

#include "timer.h"

const int32_t TIMER_MAX = 65535;

void timer_init(){
	TIM_ClockConfigTypeDef sClockSourceConfig = {0};
	TIM_MasterConfigTypeDef sMasterConfig = {0};

	htim2.Instance = TIM2;
	htim2.Init.Prescaler = 0;
	htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim2.Init.Period = 65535;
	htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

	HAL_TIM_Base_Init(&htim2);
	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig);
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig);

	HAL_TIM_Base_Start(&htim2);
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

void timer_shutdown(){
	HAL_TIM_Base_Stop(&htim2);
	HAL_TIM_Base_DeInit(&htim2);
}
