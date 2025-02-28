/*
 * trigtests.h
 *
 *  Created on: Feb 28, 2025
 *      Author: coehl
 */

#ifndef INC_TRIGTESTS_H_
#define INC_TRIGTESTS_H_

#include "stm32f1xx_hal.h"
#include "timer.h"
#include <stdlib.h>

struct TestResult{
	uint32_t average;
	uint32_t wcet;
};

struct TrigTestResults{
	struct TestResult normalSin;
	struct TestResult normalCos;
	struct TestResult taylorSin;
	struct TestResult taylorCos;
};

struct TestResult test_normalSin();
struct TestResult test_normalCos();
struct TestResult test_taylorSin();
struct TestResult test_taylorCos();

struct TrigTestResults runTrigTimerTests();
void trigTimerTestResultsToString(char *buf, struct TrigTestResults results);

void trigFunctionsTestToString(char *buf);

#endif /* INC_TRIGTESTS_H_ */
