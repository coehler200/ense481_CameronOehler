/*
 * taylortrig.h
 *
 *  Created on: Feb 27, 2025
 *      Author: coehl
 */

#ifndef INC_TAYLORTRIG_H_
#define INC_TAYLORTRIG_H_

#include "stm32f1xx_hal.h"

int sgn(double y);
double radToRange(double rad);

int16_t radToBAM(double rad);
double BAMToRad(int16_t bam);

int16_t tsin(int16_t y);
int16_t tcos(int16_t y);

#endif /* INC_TAYLORTRIG_H_ */
