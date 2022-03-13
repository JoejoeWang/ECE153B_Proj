/*
 * ECE 153B - Winter 2022
 *
 * Name(s):
 * Section:
 * Lab: 4A
 */


#include "stm32l476xx.h"

#include "LED.h"
#include "SysClock.h"
#include "UART.h"

#include <string.h>
#include <stdio.h>

int main(void) {
	System_Clock_Init(); // Switch System Clock = 80 MHz
	LED_Init();
	
	// Initialize UART -- change the argument depending on the part you are working on
	UART2_Init();
	UART2_GPIO_Init();
	USART_Init(USART2);
	
	char rxByte;
	while(1) {
		char data;
		scanf("%c",&data);
		
		if (data == 'Y' || data == 'y'){
			Green_LED_On();
			printf("You have been attacked.\n");
		}
		
		else if (data == 'N' || data == 'n'){
			Green_LED_Off();
			printf("Our system saved your ass.\n");
		}
		
		else{
			printf("Please try again with a valid command.\n");
		}
	}
}
