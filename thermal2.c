#include "stm32l476xx.h"

void Thermal2_Init() {
		// Enable HSI
    RCC->CR |= ((uint32_t)RCC_CR_HSION);
    while ( (RCC->CR & (uint32_t) RCC_CR_HSIRDY) == 0 );

    // Select HSI as system clock source
    RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
    RCC->CFGR |= (uint32_t)RCC_CFGR_SW_HSI;
    while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) == 0 );

    // Enable GPIO Clock
		RCC->AHB2ENR |=	RCC_AHB2ENR_GPIOBEN;
	
	//initialize PB4 for Thermal
	//Configure PB4 to be used as input mode function
	GPIOB->MODER &= ~GPIO_MODER_MODE4;

	//Set PB4 to no pull-up, no pull-down
	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD4;
}


int main(void) {	
	Thermal2_Init();
	uint32_t mask = 1UL<<4;

	while(1){	
		uint32_t Thermal2 = (GPIOB->IDR & mask) == mask;
	}
}
