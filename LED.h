#ifndef __STM32L476R_NUCLEO_LED_H
#define __STM32L476R_NUCLEO_LED_H

#include "stm32l476xx.h"
#include "SPI.h"
#include "SysClock.h"
#include "SysTimer.h"

void LED_Init(void);

void Green_LED_Off(void);
void Green_LED_On(void);
void Green_LED_Toggle(void);

void LED_MATRIX_Init(void);
void LED_Default(void);
void LED_1(void);
void LED_2(void);
void LED_3(void);
void LED_4(void);
void LED_5(void);


void Detect_1(void);
void Detect_2(void);
void Detect_3(void);
void Detect_4(void);
void Detect_5(void);

void present(void);
	
void LED_send(uint16_t cmd_data);
void Delay(void);

#endif
