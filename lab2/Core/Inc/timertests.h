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

struct AverageAndWCET{
	uint32_t average;
	uint32_t wcet;
};

struct TimerTestResults{
	struct AverageAndWCET addTwoRandom32BitIntegersResult;
	struct AverageAndWCET addTwoRandom64BitIntegersResult;
	struct AverageAndWCET multiplyTwoRandom32BitIntegersResult;
	struct AverageAndWCET multiplyTwoRandom64BitIntegersResult;
	struct AverageAndWCET divideTwoRandom32BitIntegersResult;
	struct AverageAndWCET divideTwoRandom64BitIntegersResult;
	struct AverageAndWCET copy8ByteStructResult;
	struct AverageAndWCET copy128ByteStructResult;
	struct AverageAndWCET copy1024ByteStructResult;
};

struct AverageAndWCET test_addTwoRandom32BitIntegers();
struct AverageAndWCET test_addTwoRandom64BitIntegers();
struct AverageAndWCET test_multiplyTwoRandom32BitIntegers();
struct AverageAndWCET test_multiplyTwoRandom64BitIntegers();
struct AverageAndWCET test_divideTwoRandom32BitIntegers();
struct AverageAndWCET test_divideTwoRandom64BitIntegers();
struct AverageAndWCET test_copy8ByteStruct();
struct AverageAndWCET test_copy128ByteStruct();
struct AverageAndWCET test_copy1024ByteStruct();

struct TimerTestResults runTimerTests();
void timerTestResultsToString(char *buf, struct TimerTestResults results);

#endif /* INC_TIMERTESTS_H_ */
