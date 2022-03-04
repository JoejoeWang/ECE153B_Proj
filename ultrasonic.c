
/*
 * ECE 153B - Winter 2022
 *
 * Name(s): Limin Ding, Xianqi Wang
 * Section: 7:00pm - 10:00pm Tuesday
 * Lab: 3B
 */
  
#include "stm32l476xx.h"
#include "LED.h"

uint32_t volatile currentValue = 0;
uint32_t volatile lastValue = 0;
uint32_t volatile overflowCount = 0;
uint32_t volatile timeInterval = 0;
uint32_t volatile intervalCount = 0;
uint32_t volatile distance = 0;

void Input_Capture_Setup() {
	//Setup PB6
	
	//Enable the clock for GPIO Port B
	RCC->AHB2ENR |=	RCC_AHB2ENR_GPIOBEN;
	GPIOB->MODER &= ~GPIO_MODER_MODE6;
	GPIOB->MODER |= GPIO_MODER_MODE6_1;
	//Configure PB6 to be used as alternative function TIM4 CH1
	GPIOB->AFR[0] |= GPIO_AFRL_AFSEL6_1;
	//Set PB6 to no pull-up, no pull-down
	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD6;
	
	//Setup Timer 4
	
	//Enable Timer 4 in RCC APB1ENR1
	RCC->APB1ENR1 |= RCC_APB1ENR1_TIM4EN;
	//Set the prescaler to 15
	TIM4->PSC |= 0x000F;
	//Enable auto reload preload
	TIM4->CR1 |= TIM_CR1_ARPE;
	//Set the auto reload value to maximum
	TIM4->ARR |= 0xFFFF;
	//Set the input capture mode 
	TIM4->CCMR1 |= TIM_CCMR1_CC1S_0;
	TIM4->CCMR1 &= ~TIM_CCMR1_CC1S_1;
	//Set bits to capture both rising/falling edges
	TIM4->CCER |= TIM_CCER_CC1P;
	TIM4->CCER |= TIM_CCER_CC1NP;
	//Enable capturing
	TIM4->CCER |= TIM_CCER_CC1E;
	//Enable both interrupt and DMA requests*
	TIM4->DIER |= TIM_DIER_UDE;
	TIM4->DIER |= TIM_DIER_CC1IE;
	//Enable the update interrupt
	TIM4->DIER |= TIM_DIER_UIE;
	//Enable update generation
	TIM4->EGR |= TIM_EGR_UG;
	//Clear the update interrupt flag
	TIM4->SR &= ~TIM_SR_UIF;
	//Set the direction of the counter
	TIM4->CR1 &= ~TIM_CR1_DIR;
	//Enable the counter
	TIM4->CR1 |= TIM_CR1_CEN;
	
	//Enable the interrupt in the NVIC and set its priority to 2
	NVIC_SetPriority(TIM4_IRQn,2);
	NVIC_EnableIRQ(TIM4_IRQn);
}

void TIM4_IRQHandler(void) {
	if (TIM4->SR & TIM_SR_UIF){
		TIM4->SR &= ~TIM_SR_UIF;
		overflowCount++;
	} 
	if (TIM4->SR & TIM_SR_CC1IF){
		TIM4->SR &= ~TIM_SR_CC1IF;
		if (GPIOB->IDR & GPIO_IDR_ID6){
			lastValue = TIM4->CCR1;
			overflowCount = 0;
		}
		else{
			currentValue = TIM4->CCR1;
			timeInterval = currentValue + (65536)*overflowCount - lastValue ;
		}
	}
}

void Trigger_Setup() {
	// Setup PA9
	
	// Enable the clock for GPIO Port A
	RCC->AHB2ENR |=	RCC_AHB2ENR_GPIOAEN;
	GPIOA->MODER &= ~GPIO_MODER_MODE9;
	GPIOA->MODER |= GPIO_MODER_MODE9_1;
	// Configure PA9 to be used as alternative function TIM1 CH2
	GPIOA->AFR[1] |= GPIO_AFRH_AFSEL9_0;
	GPIOA->AFR[1] &= ~GPIO_AFRH_AFSEL9_1;
	// Set PA9 to no pull-up, no pull-down
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD9;
	// Set the output type of PA9 to push-pull
	GPIOA->OTYPER &= ~GPIO_OTYPER_OT9;
	// Set PA9 to very high output speed
	GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED9;
	
	//Setup Timer 1
	
	//Enable Timer 1 in RCC APB2ENR
	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	//Set the prescaler to 15.
	TIM1->PSC |= 0x000F;
	//Enable auto reload preload
	TIM1->CR1 |= TIM_CR1_ARPE;
	//Set the auto reload value to maximum
	TIM1->ARR |= 0xFFFF;
	//Set the CCR value
	TIM1->CCR2 |= 0x0010;
	//Set the output compare mode in PWM mode 1 	//Enable output compare preload
	TIM1->CCMR1 |= TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2PE;
	//Enable the output in the capture/compare enable register
	TIM1->CCER |= TIM_CCER_CC2E;
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

uint16_t curr_dis;
uint16_t prev_dis;
int approach;

int main(void) {	
	// Enable High Speed Internal Clock (HSI = 16 MHz)
	RCC->CR |= RCC_CR_HSION;
	while ((RCC->CR & RCC_CR_HSIRDY) == 0); // Wait until HSI is ready
	
	// Select HSI as system clock source 
	RCC->CFGR &= ~RCC_CFGR_SW;
	RCC->CFGR |= RCC_CFGR_SW_HSI;
	while ((RCC->CFGR & RCC_CFGR_SWS) == 0); // Wait until HSI is system clock source
  
	// Input Capture Setup
	Input_Capture_Setup();
	
	// Trigger Setup
	Trigger_Setup();
	
	LED_Init();

	
	while(1) {
		// [TODO] Store your measurements on Stack
		
		for (int i = 0; i < 400000; i++){
		}
		
		if (timeInterval > 0){
			distance = timeInterval/58;
		}
		else{
			distance = 0;
		}
		
		if (prev_dis - 3 > distance){
			approach = 1;
		}
		else{
			approach = 0;
		}
		
		prev_dis = distance;
		
		if (approach == 1){
			Green_LED_On();
		}
		else{
			Green_LED_Off();
		}
		
	}
}
