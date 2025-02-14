/*
 * timertests.c
 *
 *  Created on: Oct 23, 2024
 *  Updated on: Feb 13, 2025
 *      Author: coehl
 */

#include "timertests.h"
#include "stdio.h"

const int MAX_TRIALS = 1;

struct TestStruct8Bytes{
	char bytes[8];
};

struct TestStruct128Bytes{
	char bytes[128];
};

struct TestStruct1024Bytes{
	char bytes[1024];
};

struct AverageAndWCET test_addTwoRandom32BitIntegers(){
	srand(timer_start());

	uint32_t averageTime = 0;
	uint32_t wcet = 0;

	for(int i=0; i<MAX_TRIALS; i++){
		int32_t a = rand();
		int32_t b = rand();

		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);
		uint16_t start = timer_start();

		int32_t c = a + b;

		uint16_t diff = timer_stop(start);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);
		(void)c; // Silence unused variable warnings
		if(diff > wcet){
			wcet = diff;
		}
		averageTime += diff;
	}

	struct AverageAndWCET results;
	results.average = averageTime / MAX_TRIALS;
	results.wcet = wcet;
	return results;
}

struct AverageAndWCET test_addTwoRandom64BitIntegers(){
	srand(timer_start());

	uint32_t averageTime = 0;
	uint32_t wcet = 0;

	for(int i=0; i<MAX_TRIALS; i++){
		int64_t a = rand();
		int64_t b = rand();

		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);
		uint16_t start = timer_start();

		int64_t c = a + b;

		uint16_t diff = timer_stop(start);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);
		(void)c; // Silence unused variable warnings
		if(diff > wcet){
			wcet = diff;
		}
		averageTime += diff;
	}

	struct AverageAndWCET results;
	results.average = averageTime / MAX_TRIALS;
	results.wcet = wcet;
	return results;
}

struct AverageAndWCET test_multiplyTwoRandom32BitIntegers(){
	srand(timer_start());

	uint32_t averageTime = 0;
	uint32_t wcet = 0;

	for(int i=0; i<MAX_TRIALS; i++){
		int32_t a = rand();
		int32_t b = rand();

		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);
		uint16_t start = timer_start();

		int32_t c = a * b;

		uint16_t diff = timer_stop(start);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);
		(void)c; // Silence unused variable warnings
		if(diff > wcet){
			wcet = diff;
		}
		averageTime += diff;
	}

	struct AverageAndWCET results;
	results.average = averageTime / MAX_TRIALS;
	results.wcet = wcet;
	return results;
}

struct AverageAndWCET test_multiplyTwoRandom64BitIntegers(){
	srand(timer_start());

	uint32_t averageTime = 0;
	uint32_t wcet = 0;

	for(int i=0; i<MAX_TRIALS; i++){
		int64_t a = rand();
		int64_t b = rand();

		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);
		uint16_t start = timer_start();

		int64_t c = a * b;

		uint16_t diff = timer_stop(start);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);
		(void)c; // Silence unused variable warnings
		if(diff > wcet){
			wcet = diff;
		}
		averageTime += diff;
	}

	struct AverageAndWCET results;
	results.average = averageTime / MAX_TRIALS;
	results.wcet = wcet;
	return results;
}

struct AverageAndWCET test_divideTwoRandom32BitIntegers(){
	srand(timer_start());

	uint32_t averageTime = 0;
	uint32_t wcet = 0;

	for(int i=0; i<MAX_TRIALS; i++){
		int32_t a = rand();
		int32_t b = rand();

		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);
		uint16_t start = timer_start();

		int32_t c;
		if(b == 0){
			c = 0;
		}else{
			c = a / b;
		}

		uint16_t diff = timer_stop(start);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);
		(void)c; // Silence unused variable warnings
		if(diff > wcet){
			wcet = diff;
		}
		averageTime += diff;
	}

	struct AverageAndWCET results;
	results.average = averageTime / MAX_TRIALS;
	results.wcet = wcet;
	return results;
}

struct AverageAndWCET test_divideTwoRandom64BitIntegers(){
	srand(timer_start());

	uint32_t averageTime = 0;
	uint32_t wcet = 0;

	for(int i=0; i<MAX_TRIALS; i++){
		int64_t a = rand();
		int64_t b = rand();

		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);
		uint16_t start = timer_start();

		int64_t c;
		if(b == 0){
			c = 0;
		}else{
			c = a / b;
		}

		uint16_t diff = timer_stop(start);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);
		(void)c; // Silence unused variable warnings
		if(diff > wcet){
			wcet = diff;
		}
		averageTime += diff;
	}

	struct AverageAndWCET results;
	results.average = averageTime / MAX_TRIALS;
	results.wcet = wcet;
	return results;
}

struct AverageAndWCET test_copy8ByteStruct(){
	uint32_t averageTime = 0;
	uint32_t wcet = 0;

	for(int i=0; i<MAX_TRIALS; i++){
		struct TestStruct8Bytes a = {""};

		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);
		uint16_t start = timer_start();

		struct TestStruct8Bytes b = a;

		uint16_t diff = timer_stop(start);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);
		(void)b; // Silence unused variable warnings
		if(diff > wcet){
			wcet = diff;
		}
		averageTime += diff;
	}

	struct AverageAndWCET results;
	results.average = averageTime / MAX_TRIALS;
	results.wcet = wcet;
	return results;
}

struct AverageAndWCET test_copy128ByteStruct(){
	uint32_t averageTime = 0;
	uint32_t wcet = 0;

	for(int i=0; i<MAX_TRIALS; i++){
		struct TestStruct128Bytes a = {""};

		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);
		uint16_t start = timer_start();

		struct TestStruct128Bytes b = a;

		uint16_t diff = timer_stop(start);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);
		(void)b; // Silence unused variable warnings
		if(diff > wcet){
			wcet = diff;
		}
		averageTime += diff;
	}

	struct AverageAndWCET results;
	results.average = averageTime / MAX_TRIALS;
	results.wcet = wcet;
	return results;
}

struct AverageAndWCET test_copy1024ByteStruct(){
	uint32_t averageTime = 0;
	uint32_t wcet = 0;

	for(int i=0; i<MAX_TRIALS; i++){
		struct TestStruct1024Bytes a = {""};

		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);
		uint16_t start = timer_start();

		struct TestStruct1024Bytes b = a;

		uint16_t diff = timer_stop(start);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);
		(void)b; // Silence unused variable warnings
		if(diff > wcet){
			wcet = diff;
		}
		averageTime += diff;
	}

	struct AverageAndWCET results;
	results.average = averageTime / MAX_TRIALS;
	results.wcet = wcet;
	return results;
}

struct TimerTestResults runTimerTests(){
	struct TimerTestResults results;

	timer_init();

	results.addTwoRandom32BitIntegersResult = test_addTwoRandom32BitIntegers();
	results.addTwoRandom64BitIntegersResult = test_addTwoRandom64BitIntegers();
	results.multiplyTwoRandom32BitIntegersResult =
			test_multiplyTwoRandom32BitIntegers();
	results.multiplyTwoRandom64BitIntegersResult =
			test_multiplyTwoRandom64BitIntegers();
	results.divideTwoRandom32BitIntegersResult =
			test_divideTwoRandom32BitIntegers();
	results.divideTwoRandom64BitIntegersResult =
			test_divideTwoRandom64BitIntegers();
	results.copy8ByteStructResult = test_copy8ByteStruct();
	results.copy128ByteStructResult = test_copy128ByteStruct();
	results.copy1024ByteStructResult = test_copy1024ByteStruct();

	timer_shutdown();

	return results;
}

void timerTestResultsToString(char *buf, struct TimerTestResults results){
	sprintf(buf,
		"Timer Test Results\n\r"
		"==========================\n\r"
		"Add 2 32bit Integers = %lu [wcet=%lu]\n\r"
		"Add 2 64bit Integers = %lu [wcet=%lu]\n\r"
		"Multiply 2 32bit Integers = %lu [wcet=%lu]\n\r"
		"Multiply 2 64bit Integers = %lu [wcet=%lu]\n\r"
		"Divide 2 32bit Integers = %lu [wcet=%lu]\n\r"
		"Divide 2 64bit Integers = %lu [wcet=%lu]\n\r"
		"Copy 8byte struct = %lu [wcet=%lu]\n\r"
		"Copy 128byte struct = %lu [wcet=%lu]\n\r"
		"Copy 1024byte struct = %lu [wcet=%lu]\n\r",
		results.addTwoRandom32BitIntegersResult.average,
		results.addTwoRandom32BitIntegersResult.wcet,
		results.addTwoRandom64BitIntegersResult.average,
		results.addTwoRandom64BitIntegersResult.wcet,
		results.multiplyTwoRandom32BitIntegersResult.average,
		results.multiplyTwoRandom32BitIntegersResult.wcet,
		results.multiplyTwoRandom64BitIntegersResult.average,
		results.multiplyTwoRandom64BitIntegersResult.wcet,
		results.divideTwoRandom32BitIntegersResult.average,
		results.divideTwoRandom32BitIntegersResult.wcet,
		results.divideTwoRandom64BitIntegersResult.average,
		results.divideTwoRandom64BitIntegersResult.wcet,
		results.copy8ByteStructResult.average,
		results.copy8ByteStructResult.wcet,
		results.copy128ByteStructResult.average,
		results.copy128ByteStructResult.wcet,
		results.copy1024ByteStructResult.average,
		results.copy1024ByteStructResult.wcet
	);
}
