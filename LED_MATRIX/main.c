
/*
 * ECE 153B - Winter 2022
 *
 * Name(s): Limin Ding, Xianqi Wang
 * Section: 7:00pm - 10:00pm Tuesday
 * Lab: 3B
 */
  
#include "stm32l476xx.h"
#include "LED.h"
#include "SPI.h"
#include "SysClock.h"
#include "SysTimer.h"

#include <stdio.h>

uint32_t volatile currentValue1 = 0;
uint32_t volatile lastValue1 = 0;
uint32_t volatile overflowCount1 = 0;
uint32_t volatile timeInterval1 = 0;


uint32_t volatile currentValue2 = 0;
uint32_t volatile lastValue2 = 0;
uint32_t volatile overflowCount2 = 0;
uint32_t volatile timeInterval2 = 0;


uint32_t volatile currentValue3 = 0;
uint32_t volatile lastValue3 = 0;
uint32_t volatile overflowCount3 = 0;
uint32_t volatile timeInterval3 = 0;


uint32_t volatile currentValue4 = 0;
uint32_t volatile lastValue4 = 0;
uint32_t volatile overflowCount4 = 0;
uint32_t volatile timeInterval4 = 0;


uint32_t volatile currentValue5 = 0;
uint32_t volatile lastValue5 = 0;
uint32_t volatile overflowCount5 = 0;
uint32_t volatile timeInterval5 = 0;





void Input_Capture1_Setup() {
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
		overflowCount1++;
	} 
	if (TIM4->SR & TIM_SR_CC1IF){
		TIM4->SR &= ~TIM_SR_CC1IF;
		if (GPIOB->IDR & GPIO_IDR_ID6){
			lastValue1 = TIM4->CCR1;
			overflowCount1 = 0;
		}
		else{
			currentValue1 = TIM4->CCR1;
			timeInterval1 = currentValue1 + (65536)*overflowCount1 - lastValue1 ;
		}
	}
}


void Input_Capture2_Setup() {
	//Setup PA0
	
	//Enable the clock for GPIO Port A
	RCC->AHB2ENR |=	RCC_AHB2ENR_GPIOAEN;
	GPIOA->MODER &= ~GPIO_MODER_MODE0;
	GPIOA->MODER |= GPIO_MODER_MODE0_1;
	//Configure PA0 to be used as alternative function TIM2 CH1
	GPIOA->AFR[0] |= GPIO_AFRL_AFSEL0_0;
	//Set PA0 to no pull-up, no pull-down
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD0;
	
	//Setup Timer 2
	
	//Enable Timer 2 in RCC APB1ENR1
	RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN;
	//Set the prescaler to 15
	TIM2->PSC |= 0x000F;
	//Enable auto reload preload
	TIM2->CR1 |= TIM_CR1_ARPE;
	//Set the auto reload value to maximum
	TIM2->ARR |= 0xFFFF;
	//Set the input capture mode 
	TIM2->CCMR1 |= TIM_CCMR1_CC1S_0;
	TIM2->CCMR1 &= ~TIM_CCMR1_CC1S_1;
	//Set bits to capture both rising/falling edges
	TIM2->CCER |= TIM_CCER_CC1P;
	TIM2->CCER |= TIM_CCER_CC1NP;
	//Enable capturing
	TIM2->CCER |= TIM_CCER_CC1E;
	//Enable both interrupt and DMA requests*
	TIM2->DIER |= TIM_DIER_UDE;
	TIM2->DIER |= TIM_DIER_CC1IE;
	//Enable the update interrupt
	TIM2->DIER |= TIM_DIER_UIE;
	//Enable update generation
	TIM2->EGR |= TIM_EGR_UG;
	//Clear the update interrupt flag
	TIM2->SR &= ~TIM_SR_UIF;
	//Set the direction of the counter
	TIM2->CR1 &= ~TIM_CR1_DIR;
	//Enable the counter
	TIM2->CR1 |= TIM_CR1_CEN;
	
	//Enable the interrupt in the NVIC and set its priority to 2
	NVIC_SetPriority(TIM2_IRQn,2);
	NVIC_EnableIRQ(TIM2_IRQn);
}



void TIM2_IRQHandler(void) {
	if (TIM2->SR & TIM_SR_UIF){
		TIM2->SR &= ~TIM_SR_UIF;
		overflowCount2++;
	} 
	if (TIM2->SR & TIM_SR_CC1IF){
		TIM2->SR &= ~TIM_SR_CC1IF;
		if (GPIOA->IDR & GPIO_IDR_ID0){
			lastValue2 = TIM2->CCR1;
			overflowCount2 = 0;
		}
		else{
			currentValue2 = TIM2->CCR1;
			timeInterval2 = currentValue2 + (65536)*overflowCount2 - lastValue2 ;
		}
	}
}


void Input_Capture3_Setup() {
	//Setup PB5
	
	//Enable the clock for GPIO Port B
	RCC->AHB2ENR |=	RCC_AHB2ENR_GPIOBEN;
	GPIOB->MODER &= ~GPIO_MODER_MODE5;
	GPIOB->MODER |= GPIO_MODER_MODE5_1;
	//Configure PB5 to be used as alternative function TIM3 CH2
	GPIOB->AFR[0] |= GPIO_AFRL_AFSEL5_1;
	//Set PB5 to no pull-up, no pull-down
	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD5;
	
	//Setup Timer 3
	
	//Enable Timer 3 in RCC APB1ENR1
	RCC->APB1ENR1 |= RCC_APB1ENR1_TIM3EN;
	//Set the prescaler to 15
	TIM3->PSC |= 0x000F;
	//Enable auto reload preload
	TIM3->CR1 |= TIM_CR1_ARPE;
	//Set the auto reload value to maximum
	TIM3->ARR |= 0xFFFF;
	//Set the input capture mode 
	TIM3->CCMR1 |= TIM_CCMR1_CC2S_0;
	TIM3->CCMR1 &= ~TIM_CCMR1_CC2S_1;
	//Set bits to capture both rising/falling edges
	TIM3->CCER |= TIM_CCER_CC2P;
	TIM3->CCER |= TIM_CCER_CC2NP;
	//Enable capturing
	TIM3->CCER |= TIM_CCER_CC2E;
	//Enable both interrupt and DMA requests*
	TIM3->DIER |= TIM_DIER_UDE;
	TIM3->DIER |= TIM_DIER_CC2IE;
	//Enable the update interrupt
	TIM3->DIER |= TIM_DIER_UIE;
	//Enable update generation
	TIM3->EGR |= TIM_EGR_UG;
	//Clear the update interrupt flag
	TIM3->SR &= ~TIM_SR_UIF;
	//Set the direction of the counter
	TIM3->CR1 &= ~TIM_CR1_DIR;
	//Enable the counter
	TIM3->CR1 |= TIM_CR1_CEN;
	
	//Enable the interrupt in the NVIC and set its priority to 2
	NVIC_SetPriority(TIM3_IRQn,2);
	NVIC_EnableIRQ(TIM3_IRQn);
}

void TIM3_IRQHandler(void) {
	if (TIM3->SR & TIM_SR_UIF){
		TIM3->SR &= ~TIM_SR_UIF;
		overflowCount3++;
	} 
	if (TIM3->SR & TIM_SR_CC2IF){
		TIM3->SR &= ~TIM_SR_CC2IF;
		if (GPIOB->IDR & GPIO_IDR_ID5){
			lastValue3 = TIM3->CCR2;
			overflowCount3 = 0;
		}
		else{
			currentValue3 = TIM3->CCR2;
			timeInterval3 = currentValue3 + (65536)*overflowCount3 - lastValue3 ;
		}
	}
}

void Input_Capture4_Setup() {
	//Setup PA1
	
	//Enable the clock for GPIO Port A
	RCC->AHB2ENR |=	RCC_AHB2ENR_GPIOAEN;
	GPIOA->MODER &= ~GPIO_MODER_MODE0;
	GPIOA->MODER |= GPIO_MODER_MODE0_1;
	//Configure PA0 to be used as alternative function TIM5 CH2
	GPIOA->AFR[0] |= GPIO_AFRL_AFSEL1_1;
	//Set PA0 to no pull-up, no pull-down
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD1;
	
	//Setup Timer 5
	
	//Enable Timer 5 in RCC APB1ENR1
	RCC->APB1ENR1 |= RCC_APB1ENR1_TIM5EN;
	//Set the prescaler to 15
	TIM5->PSC |= 0x000F;
	//Enable auto reload preload
	TIM5->CR1 |= TIM_CR1_ARPE;
	//Set the auto reload value to maximum
	TIM5->ARR |= 0xFFFF;
	//Set the input capture mode 
	TIM5->CCMR1 |= TIM_CCMR1_CC2S_0;
	TIM5->CCMR1 &= ~TIM_CCMR1_CC2S_1;
	//Set bits to capture both rising/falling edges
	TIM5->CCER |= TIM_CCER_CC2P;
	TIM5->CCER |= TIM_CCER_CC2NP;
	//Enable capturing
	TIM5->CCER |= TIM_CCER_CC2E;
	//Enable both interrupt and DMA requests*
	TIM5->DIER |= TIM_DIER_UDE;
	TIM5->DIER |= TIM_DIER_CC2IE;
	//Enable the update interrupt
	TIM5->DIER |= TIM_DIER_UIE;
	//Enable update generation
	TIM5->EGR |= TIM_EGR_UG;
	//Clear the update interrupt flag
	TIM5->SR &= ~TIM_SR_UIF;
	//Set the direction of the counter
	TIM5->CR1 &= ~TIM_CR1_DIR;
	//Enable the counter
	TIM5->CR1 |= TIM_CR1_CEN;
	
	//Enable the interrupt in the NVIC and set its priority to 2
	NVIC_SetPriority(TIM5_IRQn,2);
	NVIC_EnableIRQ(TIM5_IRQn);
}



void TIM5_IRQHandler(void) {
	if (TIM5->SR & TIM_SR_UIF){
		TIM5->SR &= ~TIM_SR_UIF;
		overflowCount4++;
	} 
	if (TIM5->SR & TIM_SR_CC2IF){
		TIM5->SR &= ~TIM_SR_CC2IF;
		if (GPIOA->IDR & GPIO_IDR_ID1){
			lastValue4 = TIM5->CCR2;
			overflowCount4 = 0;
		}
		else{
			currentValue4 = TIM5->CCR2;
			timeInterval4 = currentValue4 + (65536)*overflowCount4 - lastValue4 ;
		}
	}
}


void Input_Capture5_Setup() {
	//Setup PC6
	
	//Enable the clock for GPIO Port C
	RCC->AHB2ENR |=	RCC_AHB2ENR_GPIOCEN;
	GPIOC->MODER &= ~GPIO_MODER_MODE6;
	GPIOC->MODER |= GPIO_MODER_MODE6_1;
	//Configure PC6 to be used as alternative function TIM8 CH1
	GPIOC->AFR[0] |= GPIO_AFRL_AFSEL6_0;
	GPIOC->AFR[0] |= GPIO_AFRL_AFSEL6_1;
	//Set PA0 to no pull-up, no pull-down
	GPIOC->PUPDR &= ~GPIO_PUPDR_PUPD6;
	
	//Setup Timer 8
	
	//Enable Timer 5 in RCC APB1ENR1
	RCC->APB2ENR |= RCC_APB2ENR_TIM8EN;
	//Set the prescaler to 15
	TIM8->PSC |= 0x000F;
	//Enable auto reload preload
	TIM8->CR1 |= TIM_CR1_ARPE;
	//Set the auto reload value to maximum
	TIM8->ARR |= 0xFFFF;
	//Set the input capture mode 
	TIM8->CCMR1 |= TIM_CCMR1_CC1S_0;
	TIM8->CCMR1 &= ~TIM_CCMR1_CC1S_1;
	//Set bits to capture both rising/falling edges
	TIM8->CCER |= TIM_CCER_CC1P;
	TIM8->CCER |= TIM_CCER_CC1NP;
	//Enable capturing
	TIM8->CCER |= TIM_CCER_CC1E;
	//Enable both interrupt and DMA requests*
	TIM8->DIER |= TIM_DIER_UDE;
	TIM8->DIER |= TIM_DIER_CC1IE;
	//Enable the update interrupt
	TIM8->DIER |= TIM_DIER_UIE;
	//Enable update generation
	TIM8->EGR |= TIM_EGR_UG;
	//Clear the update interrupt flag
	TIM8->SR &= ~TIM_SR_UIF;
	//Set the direction of the counter
	TIM8->CR1 &= ~TIM_CR1_DIR;
	//Enable the counter
	TIM8->CR1 |= TIM_CR1_CEN;
	
	//Enable the interrupt in the NVIC and set its priority to 2
	NVIC_SetPriority(TIM8_IRQn,2);
	NVIC_EnableIRQ(TIM8_IRQn);
}



void TIM8_IRQHandler(void) {
	if (TIM8->SR & TIM_SR_UIF){
		TIM8->SR &= ~TIM_SR_UIF;
		overflowCount5++;
	} 
	if (TIM8->SR & TIM_SR_CC1IF){
		TIM8->SR &= ~TIM_SR_CC1IF;
		if (GPIOC->IDR & GPIO_IDR_ID6){
			lastValue5 = TIM8->CCR1;
			overflowCount5 = 0;
		}
		else{
			currentValue5 = TIM8->CCR1;
			timeInterval5 = currentValue5 + (65536)*overflowCount5 - lastValue5 ;
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





int curr_dis1;
int prev_dis1;
int approach1;

int curr_dis2;
int prev_dis2;
int approach2;

int curr_dis3;
int prev_dis3;
int approach3;

int curr_dis4;
int prev_dis4;
int approach4;

int curr_dis5;
int prev_dis5;
int approach5;

uint32_t volatile distance1 = 0;
uint32_t volatile distance2 = 0;
uint32_t volatile distance3 = 0;
uint32_t volatile distance4 = 0;
uint32_t volatile distance5 = 0;


int main(void) {	
	System_Clock_Init();   // System Clock = 80 MHz
	SysTick_Init();
	
	SPI2_GPIO_Init();
	SPI2_Init();
	
	LED_Init();
	LED_Default();
	
	// Enable High Speed Internal Clock (HSI = 16 MHz)
	RCC->CR |= RCC_CR_HSION;
	while ((RCC->CR & RCC_CR_HSIRDY) == 0); // Wait until HSI is ready
	
	// Select HSI as system clock source 
	RCC->CFGR &= ~RCC_CFGR_SW;
	RCC->CFGR |= RCC_CFGR_SW_HSI;
	while ((RCC->CFGR & RCC_CFGR_SWS) == 0); // Wait until HSI is system clock source
  
	// Input Capture Setup
	Input_Capture1_Setup();
	Input_Capture2_Setup();
	Input_Capture3_Setup();
	Input_Capture4_Setup();
	Input_Capture5_Setup();
	
	// Trigger Setup
	Trigger_Setup();
	
	LED_Init();

	
	while(1) {
		
		// Delay
		for (int i = 0; i < 400000; i++){
		}
		
		// Measuring distances
		if (timeInterval1 > 0){
			distance1 = timeInterval1/58;
		}
		else{
			distance1 = 0;
		}
		
		if (timeInterval2 > 0){
			distance2 = timeInterval2/58;
		}
		else{
			distance2 = 0;
		}
		
		if (timeInterval3 > 0){
			distance3 = timeInterval3/58;
		}
		else{
			distance3 = 0;
		}
		
		if (timeInterval4 > 0){
			distance4 = timeInterval4/58;
		}
		else{
			distance4 = 0;
		}

		if (timeInterval5 > 0){
			distance5 = timeInterval5/58;
		}
		else{
			distance5 = 0;
		}

		// Determine approaching direction
		if ((prev_dis1 - 5)> distance1){
			approach1 = 1;
		}
		else{
			approach1 = 0;
		}
		
		if ((prev_dis2 - 5)> distance2){
			approach2 = 1;
		}
		else{
			approach2 = 0;
		}
		
		if ((prev_dis3 - 5)> distance3){
			approach3 = 1;
		}
		else{
			approach3 = 0;
		}
		
		if ((prev_dis4 - 5)> distance4){
			approach4 = 1;
		}
		else{
			approach4 = 0;
		}
		
		if ((prev_dis5 - 5)> distance5){
			approach5 = 1;
		}
		else{
			approach5 = 0;
		}
		
		// Update the prev_dis
		prev_dis1 = distance1;
		prev_dis2 = distance2;
		prev_dis3 = distance3;
		prev_dis4 = distance4;
		prev_dis5 = distance5;
		
		// Show the result on the LED matrix
		if (approach1 == 1){
			Detect_1();
			LED_Default();
		}
		
		if (approach2 == 1){
			Detect_2();
			LED_Default();
		}
		
		if (approach3 == 1){
			Detect_3();
			LED_Default();
		}
		
		if (approach4 == 1){
			Detect_4();
			LED_Default();
		}

		if (approach5 == 1){
			Detect_5();
			LED_Default();
		}
		
	}
}
