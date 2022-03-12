#include "LED.h"

void LED_Init(void) {
	// Enable GPIO Clocks
		RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
		RCC->AHB2ENR |=	RCC_AHB2ENR_GPIOCEN;
	
	
	// Initialize Green LED
    GPIOA->MODER &=	~(3UL<<10);
		GPIOA->MODER |= 1UL<<10;
		GPIOA->OTYPER &= ~(1UL<<5);
		GPIOA->PUPDR &=	~(3UL<<10);
}

void Green_LED_Off(void) {
		GPIOA->ODR &= ~1UL<<5;
}

void Green_LED_On(void) {
		GPIOA->ODR |= 1UL<<5;
}

void Green_LED_Toggle(void) {
	uint32_t check = 1UL<<5;
	uint32_t status = (GPIOA->ODR & check) == check;
	if (status == 0){
		GPIOA->ODR |= 1UL<<5;
	}
	else{
		GPIOA->ODR &= ~1UL<<5;
	}
}
