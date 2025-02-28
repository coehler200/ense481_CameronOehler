/*
 * taylortrig.c
 *
 *  Created on: Feb 27, 2025
 *      Author: coehl
 */

#include "taylortrig.h"

short tsin(short y){
	const short S1 = 0x6488;
	const short S2 = 0x2958;
	const short S3 = 0x51a;
	const short S4 = 0x4d;

	long z, prod, sum;
	z = ((long)y * y) >> 12;

	prod = (z * S4) >> 16;
	sum = S3 - prod;
	prod = (z * sum) >> 16;
	sum = S2 - prod;
	prod = (z * sum) >> 16;
	sum = S1 - prod;

	return (short)((y * sum) >> 13);
}

short tcos(short y){
	const short C1 = 0x7fff;
	const short C2 = 0x4ef5;
	const short C3 = 0x103e;
	const short C4 = 0x156;

	long z, prod, sum;
	z = ((long)y * y) >> 12;

	prod = (z * C4) >> 16;
	sum = C3 - prod;
	prod = (z * sum) >> 16;
	sum = C2 - prod;
	prod = (z * sum) >> 15;
	sum = C1 - prod;

	return (short)(sum);
}
