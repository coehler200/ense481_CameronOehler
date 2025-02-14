/*
 * timertests.c
 *
 *  Created on: Oct 23, 2024
 *      Author: coehl
 */

#include "timertests.h"
#include "stdio.h"

const int MAX_TRIALS = 100;

struct TestStruct8Bytes{
	char bytes[8];
};

struct TestStruct128Bytes{
	char bytes[128];
};

struct TestStruct1024Bytes{
	char bytes[1024];
};

uint32_t test_addTwoRandom32BitIntegers(){
	srand(timer_start());

	uint32_t averageTime = 0;

	for(int i=0; i<MAX_TRIALS; i++){
		int32_t a = rand();
		int32_t b = rand();

		int16_t start = timer_start();

		int32_t c = a + b;

		int16_t diff = timer_stop(start);
		(void)c; // Silence unused variable warnings
		averageTime += diff;
	}

	return averageTime / MAX_TRIALS;
}

uint32_t test_addTwoRandom64BitIntegers(){
	srand(timer_start());

	uint32_t averageTime = 0;

	for(int i=0; i<MAX_TRIALS; i++){
		int64_t a = rand();
		int64_t b = rand();

		int16_t start = timer_start();

		int64_t c = a + b;

		int16_t diff = timer_stop(start);
		(void)c; // Silence unused variable warnings
		averageTime += diff;
	}

	return averageTime / MAX_TRIALS;
}

uint32_t test_multiplyTwoRandom32BitIntegers(){
	srand(timer_start());

	uint32_t averageTime = 0;

	for(int i=0; i<MAX_TRIALS; i++){
		int32_t a = rand();
		int32_t b = rand();

		int16_t start = timer_start();

		int32_t c = a * b;

		int16_t diff = timer_stop(start);
		(void)c; // Silence unused variable warnings
		averageTime += diff;
	}

	return averageTime / MAX_TRIALS;
}

uint32_t test_multiplyTwoRandom64BitIntegers(){
	srand(timer_start());

	uint32_t averageTime = 0;

	for(int i=0; i<MAX_TRIALS; i++){
		int64_t a = rand();
		int64_t b = rand();

		int16_t start = timer_start();

		int64_t c = a * b;

		int16_t diff = timer_stop(start);
		(void)c; // Silence unused variable warnings
		averageTime += diff;
	}

	return averageTime / MAX_TRIALS;
}

uint32_t test_divideTwoRandom32BitIntegers(){
	srand(timer_start());

	uint32_t averageTime = 0;

	for(int i=0; i<MAX_TRIALS; i++){
		int32_t a = rand();
		int32_t b = rand();

		int16_t start = timer_start();

		int32_t c;
		if(b == 0){
			c = 0;
		}else{
			c = a / b;
		}

		int16_t diff = timer_stop(start);
		(void)c; // Silence unused variable warnings
		averageTime += diff;
	}

	return averageTime / MAX_TRIALS;
}

uint32_t test_divideTwoRandom64BitIntegers(){
	srand(timer_start());

	uint32_t averageTime = 0;

	for(int i=0; i<MAX_TRIALS; i++){
		int64_t a = rand();
		int64_t b = rand();

		int16_t start = timer_start();

		int64_t c;
		if(b == 0){
			c = 0;
		}else{
			c = a / b;
		}

		int16_t diff = timer_stop(start);
		(void)c; // Silence unused variable warnings
		averageTime += diff;
	}

	return averageTime / MAX_TRIALS;
}

uint32_t test_copy8ByteStruct(){
	uint32_t averageTime = 0;

	for(int i=0; i<MAX_TRIALS; i++){
		struct TestStruct8Bytes a = {""};

		int16_t start = timer_start();

		struct TestStruct8Bytes b = a;

		int16_t diff = timer_stop(start);
		(void)b; // Silence unused variable warnings
		averageTime += diff;
	}

	return averageTime / MAX_TRIALS;
}

uint32_t test_copy128ByteStruct(){
	uint32_t averageTime = 0;

	for(int i=0; i<MAX_TRIALS; i++){
		struct TestStruct128Bytes a = {""};

		int16_t start = timer_start();

		struct TestStruct128Bytes b = a;

		int16_t diff = timer_stop(start);
		(void)b; // Silence unused variable warnings
		averageTime += diff;
	}

	return averageTime / MAX_TRIALS;
}

uint32_t test_copy1024ByteStruct(){
	uint32_t averageTime = 0;

	for(int i=0; i<MAX_TRIALS; i++){
		struct TestStruct1024Bytes a = {""};

		int16_t start = timer_start();

		struct TestStruct1024Bytes b = a;

		int16_t diff = timer_stop(start);
		(void)b; // Silence unused variable warnings
		averageTime += diff;
	}

	return averageTime / MAX_TRIALS;
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
		"Add 2 32bit Integers = %lu\n\r"
		"Add 2 64bit Integers = %lu\n\r"
		"Multiply 2 32bit Integers = %lu\n\r"
		"Multiply 2 64bit Integers = %lu\n\r"
		"Divide 2 32bit Integers = %lu\n\r"
		"Divide 2 64bit Integers = %lu\n\r"
		"Copy 8byte struct = %lu\n\r"
		"Copy 128byte struct = %lu\n\r"
		"Copy 1024byte struct = %lu\n\r",
		results.addTwoRandom32BitIntegersResult,
		results.addTwoRandom64BitIntegersResult,
		results.multiplyTwoRandom32BitIntegersResult,
		results.multiplyTwoRandom64BitIntegersResult,
		results.divideTwoRandom32BitIntegersResult,
		results.divideTwoRandom64BitIntegersResult,
		results.copy8ByteStructResult,
		results.copy128ByteStructResult,
		results.copy1024ByteStructResult
	);
}
