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

double genTestVal(){
	double min = -M_PI;
	double max = M_PI;
	double range = (max - min);
	double div = RAND_MAX / range;
	return min + (rand() / div);
}

struct TestResult test_normalSin(){
	uint32_t averageTime = 0;
	uint32_t wcet = 0;

	for(int i=0; i<MAX_TRIG_TRIALS; i++){
		double y = genTestVal();

		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);
		uint16_t start = timer_start();

		volatile double x = sin(y);

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
		double y = genTestVal();

		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);
		uint16_t start = timer_start();

		volatile double x = cos(y);

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
		double _y = radToRange(genTestVal());
		int32_t y = radToBAM(_y);

		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);
		uint16_t start = timer_start();

		volatile int32_t x = tsin(y);

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
		double _y = radToRange(genTestVal());
		int32_t y = radToBAM(_y);

		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);
		uint16_t start = timer_start();

		volatile int32_t x = tcos(y);

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

	srand(timer_start());

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
	timer_init();
	srand(timer_start());

	//double rad = genTestVal();

	timer_shutdown();

	double rad = 0.0872665;
	int16_t bam = radToBAM(rad);

	double normalSin = sin(rad);
	double normalCos = cos(rad);
	double taylorSin = BAMToRad(tsin(bam));
	double taylorCos = BAMToRad(tcos(bam));

	sprintf(buf,
		"Trig Results\n\r"
		"==========================\n\r"
		"rad = %f\n\r"
		"bam = 0x%02X\n\r"
		"rad_to_bam_to_rad = %f\n\r"
		"normal sin = %f\n\r"
		"normal cos = %f\n\r"
		"taylor sin = %f\n\r"
		"taylor cos = %f\n\r",
		rad,
		bam,
		BAMToRad(bam),
		normalSin,
		normalCos,
		taylorSin,
		taylorCos
	);
}
