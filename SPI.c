#include "SPI.h"

// Note: When the data frame size is 8 bit, "SPIx->DR = byte_data;" works incorrectly. 
// It mistakenly send two bytes out because SPIx->DR has 16 bits. To solve the program,
// we should use "*((volatile uint8_t*)&SPIx->DR) = byte_data";

void SPI2_GPIO_Init(void) {
	//Enable
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
	//Mode
	GPIOB->MODER &= ~GPIO_MODER_MODE13;
	GPIOB->MODER |= GPIO_MODER_MODE13_1;
	GPIOB->MODER &= ~GPIO_MODER_MODE12;
	GPIOB->MODER |= GPIO_MODER_MODE12_1;
	GPIOB->MODER &= ~GPIO_MODER_MODE15;
	GPIOB->MODER |= GPIO_MODER_MODE15_1;
	//Alternate function selection
	GPIOB->AFR[1] |= GPIO_AFRH_AFSEL13_0;
	GPIOB->AFR[1] &= ~GPIO_AFRH_AFSEL13_1;
	GPIOB->AFR[1] |= GPIO_AFRH_AFSEL13_2;
	GPIOB->AFR[1] &= ~GPIO_AFRH_AFSEL13_3;
	GPIOB->AFR[1] |= GPIO_AFRH_AFSEL12_0;
	GPIOB->AFR[1] &= ~GPIO_AFRH_AFSEL12_1;
	GPIOB->AFR[1] |= GPIO_AFRH_AFSEL12_2;
	GPIOB->AFR[1] &= ~GPIO_AFRH_AFSEL12_3;
	GPIOB->AFR[1] |= GPIO_AFRH_AFSEL15_0;
	GPIOB->AFR[1] &= ~GPIO_AFRH_AFSEL15_1;
	GPIOB->AFR[1] |= GPIO_AFRH_AFSEL15_2;
	GPIOB->AFR[1] &= ~GPIO_AFRH_AFSEL15_3;
	//Output Type
	GPIOB->OTYPER &= ~GPIO_OTYPER_OT13;
	GPIOB->OTYPER &= ~GPIO_OTYPER_OT12;
	GPIOB->OTYPER &= ~GPIO_OTYPER_OT15;
	//Output Speed
	GPIOB->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR13;
	GPIOB->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR12;
	GPIOB->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR15;
	//Pull-Up/Down
	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD13;
	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD12;
	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD15;
	
}

void SPI2_Init(void){
	RCC->APB1ENR1 |= RCC_APB1ENR1_SPI2EN;
	RCC->APB1RSTR1 |= RCC_APB1RSTR1_SPI2RST;
	RCC->APB1RSTR1 &= ~(RCC_APB1RSTR1_SPI2RST);
	SPI2->CR1 &= ~(SPI_CR1_SPE);
	SPI2->CR1 &= ~(SPI_CR1_RXONLY);
	SPI2->CR1 &= ~(SPI_CR1_BIDIMODE);
	SPI2->CR1 &= ~(SPI_CR1_BIDIOE);
	SPI2->CR1 &= ~(SPI_CR1_LSBFIRST);
	//SPI2->CR1 &= ~(SPI_CR1_CRCL);
	SPI2->CR2 |= SPI_CR2_DS_0;
	SPI2->CR2 |= SPI_CR2_DS_1;
	SPI2->CR2 |= SPI_CR2_DS_2;
	SPI2->CR2 |= SPI_CR2_DS_3;
	SPI2->CR2 &= ~(SPI_CR2_FRF);
	SPI2->CR1 &= ~(SPI_CR1_CPOL);
	SPI2->CR1 &= ~(SPI_CR1_CPHA);
	SPI2->CR1 |= SPI_CR1_BR_0;
	SPI2->CR1 |= SPI_CR1_BR_1;
	SPI2->CR1 &= ~(SPI_CR1_BR_2);
	SPI2->CR1 &= ~(SPI_CR1_CRCEN);
	SPI2->CR1 |= SPI_CR1_MSTR;
	SPI2->CR1 |= SPI_CR1_SSM;
	SPI2->CR2 |= SPI_CR2_NSSP;
	SPI2->CR2 |= SPI_CR2_FRXTH;
	SPI2->CR1 |= SPI_CR1_SPE;
	// TODO: initialize SPI2 peripheral
}
 
//void SPI_Transfer_Byte(SPI_TypeDef* SPIx, uint16_t write_data) {
//	// TODO: perform SPI transfer

//	for (int i = 0; i < 16; i++){
//		//Write one bit data MSB first
//		while((SPI_SR_TXE & SPIx->SR) == 0)
//		{
//		}
//		*((volatile uint16_t*)&SPIx->DR) = (write_data & 0x80); 
//		while((SPI_SR_BSY & SPIx->SR)== SPI_SR_BSY){
//		}
//		//Shift the data to the left
//		write_data = write_data<<1;
//	}
//}

void SPI_Transfer_Byte(SPI_TypeDef* SPIx, uint16_t write_data) {
	// TODO: perform SPI transfer
	while((SPI_SR_TXE & SPIx->SR) == 0)
	{
	}
	*((volatile uint16_t*)&SPIx->DR) = write_data; 
	while((SPI_SR_BSY & SPIx->SR)== SPI_SR_BSY)
	{
	}
}
