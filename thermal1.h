#ifndef THERMAL_H
#define THERMAL_H

#include "stm32l476xx.h"
#include "SPI.h"
#include "SysClock.h"
#include "SysTimer.h"

void Thermal1_Init();
int get_thermal1(void);

#endif
