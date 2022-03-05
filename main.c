/*
 * ECE 153B - Winter 2022
 *
 * Name(s): Limin Ding, Xianqi Wang
 * Section: 7:00pm - 10:00pm Tuesday
 * Lab: 3B
 */
  
#include "stm32l476xx.h"
#include "LED.h"

void Init() {
	    // Enable HSI
    RCC->CR |= ((uint32_t)RCC_CR_HSION);
    while ( (RCC->CR & (uint32_t) RCC_CR_HSIRDY) == 0 );

    // Select HSI as system clock source
    RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
    RCC->CFGR |= (uint32_t)RCC_CFGR_SW_HSI;
    while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) == 0 );

    // Enable GPIO Clock
		RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
		RCC->AHB2ENR |=	RCC_AHB2ENR_GPIOBEN;

    // Initialize Green LED
    GPIOA->MODER &=	~(3UL<<10);
		GPIOA->MODER |= 1UL<<10;
		GPIOA->OTYPER &= ~(1UL<<5);
		GPIOA->PUPDR &=	~(3UL<<10);
	
	//initialize PB6 for Thermal
	//RCC->AHB2ENR |=	RCC_AHB2ENR_GPIOBEN;
	//Configure PB6 to be used as input mode function
	GPIOB->MODER &= ~GPIO_MODER_MODE6;

	//Set PB6 to no pull-up, no pull-down
	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD6;
}


int main(void) {	
	Init();
	GPIOA->ODR |= 1UL<<5;
	
		uint32_t timer = 0;
		uint32_t count = 0;
		uint32_t mask = 1UL<<6;
		uint32_t check = 1UL<<5;
		uint32_t pressed = 0;
	
		while(1){	
			uint32_t input = (GPIOB->IDR & mask) == mask;
			uint32_t status = (GPIOA->ODR & check) == check;
			
			if(input == 1){
				//button is not pressed
				GPIOA->ODR |= 1UL<<5;
			}else{
				//button is pressed
				GPIOA->ODR &= ~1UL<<5;
			}
		}
}
