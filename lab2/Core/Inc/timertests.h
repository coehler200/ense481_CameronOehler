/*
 * timertests.h
 *
 *  Created on: Oct 23, 2024
 *  Updated on: Feb 13, 2025
 *      Author: coehl
 */

#ifndef INC_TIMERTESTS_H_
#define INC_TIMERTESTS_H_

#include "stm32f1xx_hal.h"
#include "timer.h"
#include <stdlib.h>

struct TimerTestResults{
	uint32_t addTwoRandom32BitIntegersResult;
	uint32_t addTwoRandom64BitIntegersResult;
	uint32_t multiplyTwoRandom32BitIntegersResult;
	uint32_t multiplyTwoRandom64BitIntegersResult;
	uint32_t divideTwoRandom32BitIntegersResult;
	uint32_t divideTwoRandom64BitIntegersResult;
	uint32_t copy8ByteStructResult;
	uint32_t copy128ByteStructResult;
	uint32_t copy1024ByteStructResult;
};

uint32_t test_addTwoRandom32BitIntegers();
uint32_t test_addTwoRandom64BitIntegers();
uint32_t test_multiplyTwoRandom32BitIntegers();
uint32_t test_multiplyTwoRandom64BitIntegers();
uint32_t test_divideTwoRandom32BitIntegers();
uint32_t test_divideTwoRandom64BitIntegers();
uint32_t test_copy8ByteStruct();
uint32_t test_copy128ByteStruct();
uint32_t test_copy1024ByteStruct();

struct TimerTestResults runTimerTests();
void timerTestResultsToString(char *buf, struct TimerTestResults results);

#endif /* INC_TIMERTESTS_H_ */
