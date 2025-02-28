/*
 * trigtests.c
 *
 *  Created on: Feb 28, 2025
 *      Author: coehl
 */

#include "trigtests.h"
#include "stdio.h"
#include "math.h"
#include "taylortrig.h"

const int MAX_TRIG_TRIALS = 100;

struct TestResult test_normalSin(){
	srand(timer_start());

	uint32_t averageTime = 0;
	uint32_t wcet = 0;

	for(int i=0; i<MAX_TRIG_TRIALS; i++){
		short y = (short)rand();

		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);
		uint16_t start = timer_start();

		volatile short x = sin(y);

		uint16_t diff = timer_stop(start);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);
		(void)x; // Silence unused variable warnings
		if(diff > wcet){
			wcet = diff;
		}
		averageTime += diff;
	}

	struct TestResult results;
	results.average = averageTime / MAX_TRIG_TRIALS;
	results.wcet = wcet;
	return results;
}

struct TestResult test_normalCos(){
	srand(timer_start());

	uint32_t averageTime = 0;
	uint32_t wcet = 0;

	for(int i=0; i<MAX_TRIG_TRIALS; i++){
		short y = (short)rand();

		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);
		uint16_t start = timer_start();

		volatile short x = cos(y);

		uint16_t diff = timer_stop(start);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);
		(void)x; // Silence unused variable warnings
		if(diff > wcet){
			wcet = diff;
		}
		averageTime += diff;
	}

	struct TestResult results;
	results.average = averageTime / MAX_TRIG_TRIALS;
	results.wcet = wcet;
	return results;
}

struct TestResult test_taylorSin(){
	srand(timer_start());

	uint32_t averageTime = 0;
	uint32_t wcet = 0;

	for(int i=0; i<MAX_TRIG_TRIALS; i++){
		short y = (short)rand();

		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);
		uint16_t start = timer_start();

		volatile short x = tsin(y);

		uint16_t diff = timer_stop(start);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);
		(void)x; // Silence unused variable warnings
		if(diff > wcet){
			wcet = diff;
		}
		averageTime += diff;
	}

	struct TestResult results;
	results.average = averageTime / MAX_TRIG_TRIALS;
	results.wcet = wcet;
	return results;
}

struct TestResult test_taylorCos(){
	srand(timer_start());

	uint32_t averageTime = 0;
	uint32_t wcet = 0;

	for(int i=0; i<MAX_TRIG_TRIALS; i++){
		short y = (short)rand();

		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);
		uint16_t start = timer_start();

		volatile short x = tcos(y);

		uint16_t diff = timer_stop(start);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);
		(void)x; // Silence unused variable warnings
		if(diff > wcet){
			wcet = diff;
		}
		averageTime += diff;
	}

	struct TestResult results;
	results.average = averageTime / MAX_TRIG_TRIALS;
	results.wcet = wcet;
	return results;
}

struct TrigTestResults runTrigTimerTests(){
	struct TrigTestResults results;

	timer_init();

	results.normalSin = test_normalSin();
	results.normalCos = test_normalCos();
	results.taylorSin = test_taylorSin();
	results.taylorCos = test_taylorCos();

	timer_shutdown();

	return results;
}

void trigTimerTestResultsToString(char *buf, struct TrigTestResults results){
	sprintf(buf,
		"Trig Timer Test Results\n\r"
		"==========================\n\r"
		"normal sin = %lu [wcet=%lu]\n\r"
		"normal cos = %lu [wcet=%lu]\n\r"
		"taylor sin = %lu [wcet=%lu]\n\r"
		"taylor cos = %lu [wcet=%lu]\n\r",
		results.normalSin.average,
		results.normalSin.wcet,
		results.normalCos.average,
		results.normalCos.wcet,
		results.taylorSin.average,
		results.taylorSin.wcet,
		results.taylorCos.average,
		results.taylorCos.wcet
	);
}

void trigFunctionsTestToString(char *buf){
	short y = 0x1555;

	short normalSin = sin(y);
	short normalCos = cos(y);
	short taylorSin = tsin(y);
	short taylorCos = tcos(y);

	sprintf(buf,
		"Trig Results\n\r"
		"==========================\n\r"
		"normal sin = %hd\n\r"
		"normal cos = %hd\n\r"
		"taylor sin = %hd\n\r"
		"taylor cos = %hd\n\r",
		normalSin,
		normalCos,
		taylorSin,
		taylorCos
	);
}
