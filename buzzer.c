#include "buzzer.h"

void Buzzer_Trigger_Setup() {
	// Setup PA10
	
	// Enable the clock for GPIO Port A
	RCC->AHB2ENR |=	RCC_AHB2ENR_GPIOAEN;
	GPIOA->MODER &= ~GPIO_MODER_MODE10;
	GPIOA->MODER |= GPIO_MODER_MODE10_1;
	// Configure PA10 to be used as alternative function TIM1 CH2
	GPIOA->AFR[1] |= GPIO_AFRH_AFSEL10_0;
	GPIOA->AFR[1] &= ~GPIO_AFRH_AFSEL10_1;
	// Set PA10 to no pull-up, no pull-down
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD10;
	// Set the output type of PA9 to push-pull
	GPIOA->OTYPER &= ~GPIO_OTYPER_OT10;
	// Set PA9 to very high output speed
	GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED10;
	
	//Setup Timer 1
	
	//Enable Timer 1 in RCC APB2ENR
	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	//Set the prescaler to 0.
	TIM1->PSC |= 0x0000;
	//Enable auto reload preload
	TIM1->CR1 |= TIM_CR1_ARPE;
	//Set the auto reload value to maximum
	TIM1->ARR |= 0xFFFF;
	//Set the CCR value
	TIM1->CCR3 |= 0x8000;
	//Set the output compare mode in PWM mode 1 	//Enable output compare preload
	TIM1->CCMR2 |= TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3PE;
	//Enable the output in the capture/compare enable register
	TIM1->CCER |= TIM_CCER_CC3E;
	//Break and Dead-time register
	//Main output enable	//off-state selection for run mode
	TIM1->BDTR |= TIM_BDTR_MOE | TIM_BDTR_OSSR;
	//Event Generation register
	//Enable update generation
	TIM1->EGR |= TIM_EGR_UG;
	//Enable update interrupt and clear the update interrupt flag
	TIM1->DIER |= TIM_DIER_UIE;
	TIM1->SR &= ~TIM_SR_UIF;
	//Set the direction of the counter to downcounter	//Enable the counter
	TIM1->CR1 |= TIM_CR1_DIR | TIM_CR1_CEN;
}

void Buzzer_On(void) {	
	// Enable High Speed Internal Clock (HSI = 16 MHz)
	RCC->CR |= RCC_CR_HSION;
	while ((RCC->CR & RCC_CR_HSIRDY) == 0); // Wait until HSI is ready
	
	// Select HSI as system clock source 
	RCC->CFGR &= ~RCC_CFGR_SW;
	RCC->CFGR |= RCC_CFGR_SW_HSI;
	while ((RCC->CFGR & RCC_CFGR_SWS) == 0); // Wait until HSI is system clock source

	// Trigger Setup
	Buzzer_Trigger_Setup();
	
}