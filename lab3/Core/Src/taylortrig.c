/*
 * taylortrig.c
 *
 *  Created on: Feb 27, 2025
 *      Author: coehl
 */

#include "taylortrig.h"
#include "math.h"

const int64_t BAM_RES = pow(2, 16);

int sgn(double y){
	if(y >= 0) return 1;
	return -1;
}

// Converts any rad value to one in the range -PI to PI
double radToRange(double rad){
	return rad;
	if(rad > M_PI){
		rad = rad - M_PI;
	}
	else if(rad < -M_PI){
		rad = rad + M_PI;
	}
	return rad;
}

// Pre: rad between -PI & PI
int16_t radToBAM(double rad){
	double round = 0.5*sgn(rad);
	double result = (rad/(2*M_PI)) * BAM_RES;
	return (int16_t)(result+round);
}

// Pre: bam between -PI & PI in bam units
double BAMToRad(int16_t bam){
	return (bam*M_PI*2) / BAM_RES;
}

int16_t tsin(int16_t y){
	const int16_t S1 = 0x6488;
	const int16_t S3 = 0x2958;
	const int16_t S5 = 0x051a;
	const int16_t S7 = 0x004d;

	int64_t z, prod, sum;
	z = ((int64_t)y * y) >> 12;

	prod = (z * S7) >> 16;
	sum = S5 - prod;
	prod = (z * sum) >> 16;
	sum = S3 - prod;
	prod = (z * sum) >> 16;
	sum = S1 - prod;

	return (int16_t)((y * sum) >> 13);
}

int16_t tcos(int16_t y){
	const int16_t C0 = 0x7fff;
	const int16_t C2 = 0x4ef5;
	const int16_t C4 = 0x103e;
	const int16_t C6 = 0x0156;

	int64_t z, prod, sum;
	z = ((int64_t)y * y) >> 12;

	prod = (z * C6) >> 16;
	sum = C4 - prod;
	prod = (z * sum) >> 16;
	sum = C2 - prod;
	prod = (z * sum) >> 15;
	sum = C0 - prod;

	return (int16_t)(sum);
}
