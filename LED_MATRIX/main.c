/*
 * ECE 153B - Winter 2022
 *
 * Name(s):
 * Section:
 * Lab: 4C
 */


#include "stm32l476xx.h"
#include "LED.h"
#include "SPI.h"
#include "SysClock.h"
#include "SysTimer.h"

#include <stdio.h>

#define SPI_MASTER SPI2
#define SPI_SLAVE SPI3

uint8_t transmit = 0;
uint8_t receive = 0;


int main(void){
	System_Clock_Init();   // System Clock = 80 MHz
	SysTick_Init();
	
	SPI2_GPIO_Init();
	SPI2_Init();
	
	LED_Init();
	
	Detect_1();
	Detect_2();
	Detect_3();
	Detect_4();
	Detect_5();


	
}
