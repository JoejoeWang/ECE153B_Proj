/*
 * ECE 153B - Winter 2021
 *
 * Name(s):
 * Section:
 * Lab: 4C
 */

#include "LED.h"


void LED_Init(void) {
	LED_send(0x0900);       //  no decoding
	LED_send(0x0A0F);       //  brightness intensity
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
	for (int i = 0; i < 5 ; i++){
		LED_Default();
		Delay();
		LED_1();
		Delay();
		LED_Default();
	}
}

void Detect_2(void){
	for (int i = 0; i < 5 ; i++){
		LED_Default();
		Delay();
		LED_2();
		Delay();
		LED_Default();
	}
}

void Detect_3(void){
	for (int i = 0; i < 5 ; i++){
		LED_Default();
		Delay();
		LED_3();
		Delay();
		LED_Default();
	}
}

void Detect_4(void){
	for (int i = 0; i < 5 ; i++){
		LED_Default();
		Delay();
		LED_4();
		Delay();
		LED_Default();
	}
}

void Detect_5(void){
	for (int i = 0; i < 5 ; i++){
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
	for (int i = 0; i < 200000; i++){
	}
}
