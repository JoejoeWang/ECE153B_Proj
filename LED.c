#include "LED.h"
#include "SPI.h"

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

void LED_MATRIX_Init(void) {
	LED_send(0x0900);       //  no decoding
	LED_send(0x0A03);       //  brightness intensity
	LED_send(0x0b07);       //  scan limit = 8 LEDs
	LED_send(0x0c01);       //  power down =0,normal mode = 1
	LED_send(0x0F00);       //  enable test display
}

void LED_Default(void){
	LED_send(0x0118);
	LED_send(0x0218);
	LED_send(0x033c);
	LED_send(0x0481);
	LED_send(0x0500);
	LED_send(0x0642);
	LED_send(0x0700);
	LED_send(0x0818);
}

void LED_1(void){
	LED_send(0x0118);
	LED_send(0x0218);
	LED_send(0x033c);
	LED_send(0x0401);
	LED_send(0x0500);
	LED_send(0x0642);
	LED_send(0x0700);
	LED_send(0x0818);
}

void LED_2(void){
	LED_send(0x0118);
	LED_send(0x0218);
	LED_send(0x033c);
	LED_send(0x0481);
	LED_send(0x0500);
	LED_send(0x0602);
	LED_send(0x0700);
	LED_send(0x0818);
}

void LED_3(void){
	LED_send(0x0118);
	LED_send(0x0218);
	LED_send(0x033c);
	LED_send(0x0481);
	LED_send(0x0500);
	LED_send(0x0642);
	LED_send(0x0700);
	LED_send(0x0800);
}

void LED_4(void){
	LED_send(0x0118);
	LED_send(0x0218);
	LED_send(0x033c);
	LED_send(0x0481);
	LED_send(0x0500);
	LED_send(0x0640);
	LED_send(0x0700);
	LED_send(0x0818);
}

void LED_5(void){
	LED_send(0x0118);
	LED_send(0x0218);
	LED_send(0x033c);
	LED_send(0x0480);
	LED_send(0x0500);
	LED_send(0x0642);
	LED_send(0x0700);
	LED_send(0x0818);
}


void Detect_1(void){
	for (int i = 0; i < 20 ; i++){
		LED_Default();
		Delay();
		LED_1();
		Delay();
		LED_Default();
	}
}

void Detect_2(void){
	for (int i = 0; i < 20 ; i++){
		LED_Default();
		Delay();
		LED_2();
		Delay();
		LED_Default();
	}
}

void Detect_3(void){
	for (int i = 0; i < 20 ; i++){
		LED_Default();
		Delay();
		LED_3();
		Delay();
		LED_Default();
	}
}

void Detect_4(void){
	for (int i = 0; i < 20 ; i++){
		LED_Default();
		Delay();
		LED_4();
		Delay();
		LED_Default();
	}
}

void Detect_5(void){
	for (int i = 0; i < 20 ; i++){
		LED_Default();
		Delay();
		LED_5();
		Delay();
		LED_Default();
	}
}



void LED_send(uint16_t cmd_data){
	GPIOB->BSRR |= GPIO_BSRR_BR12;
	SPI_Transfer_Byte(SPI2,cmd_data);
	GPIOB->BSRR |= GPIO_BSRR_BS12;
}

void Delay(void){
	for (int i = 0; i < 1000000; i++){
	}
}

void present(void){
	//LED Matrix
	System_Clock_Init();   // System Clock = 80 MHz
	SysTick_Init();
	
	SPI2_GPIO_Init();
	SPI2_Init();
	
	LED_MATRIX_Init();
	
	Detect_1();
	Detect_2();
	Detect_3();
	Detect_4();
	Detect_5();	
}

