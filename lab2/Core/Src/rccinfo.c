/*
 * rccinfo.c
 *
 *  Created on: Feb 14, 2025
 *      Author: coehl
 */

#include "rccinfo.h"
#include <math.h>
#include <string.h>
#include <stdio.h>

void getRCCInfoString(char* buf){
	int pllmul = (int)((RCC->CFGR & 0x003C0000) >> 18) + 2; // 2,3,4,5,6,7,8,9,10,11,12,13,14,15,16
	int pllxtpre = (int)((RCC->CFGR & 0x00020000) >> 17) + 1; // 1,2
	char* pllsrc = (RCC->CFGR & 0x00010000) ?
			"HSE oscillator clock selected as PLL input clock" :
			"HSI oscillator clock / 2 selected as PLL input clock";
	int adcpre = (int)((RCC->CFGR & 0x0000C000) >> 14) * 2 + 2; // 2,4,6,8
	int ppre2 = (RCC->CFGR & 0x00002000) ? pow(2, (int)((RCC->CFGR & 0x00001800) >> 11) + 1) : 1; // 1,2,4,8,16
	int ppre1 = (RCC->CFGR & 0x00000400) ? pow(2, (int)((RCC->CFGR & 0x00000300) >> 8) + 1) : 1; // 1,2,4,8,16
	int hpre = (RCC->CFGR & 0x00000080) ? pow(2, (int)((RCC->CFGR & 0x00000070) >> 4) + 1) : 1; // 1,2,4,8,16,64,128,256,512
	sprintf(buf, "RCC_CFGR=0x%08lX\r\n"
			"PLL multiplication factor x%d\r\n"
			"HSE divider for PLL entry /%d\r\n"
			"%s\r\n"
			"ADC prescaler /%d\r\n"
			"APB2 prescaler /%d\r\n"
			"APB1 prescaler /%d\r\n"
			"AHB prescaler /%d\r\n", RCC->CFGR, pllmul, pllxtpre, pllsrc, adcpre, ppre2, ppre1, hpre);
	if((RCC->CFGR & 0x0000000C >> 2) == 0){
		strcat(buf, "HSI oscillator used as system clock\r\n");
	}
	else if((RCC->CFGR & 0x0000000C >> 2) == 1){
		strcat(buf, "HSE oscillator used as system clock\r\n");
	}
	else if((RCC->CFGR & 0x0000000C >> 2) == 2){
		strcat(buf, "PLL used as system clock\r\n");
	}
}
