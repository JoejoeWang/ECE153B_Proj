#include "stm32l476xx.h"

void Thermal1_Init() {
	// Enable HSI
	RCC->CR |= ((uint32_t)RCC_CR_HSION);
	while ( (RCC->CR & (uint32_t) RCC_CR_HSIRDY) == 0 );

	// Select HSI as system clock source
	RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
	RCC->CFGR |= (uint32_t)RCC_CFGR_SW_HSI;
	while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) == 0 );

	// Enable GPIO Clock
	RCC->AHB2ENR |=	RCC_AHB2ENR_GPIOBEN;
	
	//initialize PB6 for Thermal
	//Configure PB3 to be used as input mode function
	GPIOB->MODER &= ~GPIO_MODER_MODE3;

	//Set PB3 to no pull-up, no pull-down
	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD3;
}


int main(void) {	
	Thermal1_Init();
	uint32_t mask = 1UL<<3;
	while(1){	
		uint32_t Thermal1 = (GPIOB->IDR & mask) == mask;
	}
}
