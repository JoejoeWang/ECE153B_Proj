/*
 * ECE 153B - Winter 2021
 *
 * Name(s):
 * Section:
 * Lab: 4C
 */

#ifndef __STM32L476G_DISCOVERY_LED_H
#define __STM32L476G_DISCOVERY_LED_H

#include "stm32l476xx.h"

void LED_Init(void);
void LED_Default(void);
void LED_1(void);
void LED_2(void);
void LED_3(void);
void LED_4(void);
void LED_5(void);
void LED_6(void);
void LED_7(void);

void Detect_1(void);
void Detect_2(void);
void Detect_3(void);
void Detect_4(void);
void Detect_5(void);
void Detect_6(void);
void Detect_7(void);
	
void LED_send(uint16_t cmd_data);
void Delay(void);

#endif
