#ifndef __STM32L476R_NUCLEO_SPI_H
#define __STM32L476R_NUCLEO_SPI_H

#include "stm32l476xx.h"

void SPI2_GPIO_Init(void);
void SPI2_Init(void);
void SPI_Transfer_Byte(SPI_TypeDef* SPIx, uint16_t write_data);


#endif 
