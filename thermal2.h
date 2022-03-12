#ifndef THERMAL_H
#define THERMAL_H

#include "stm32l476xx.h"
#include "SPI.h"
#include "SysClock.h"
#include "SysTimer.h"

void Thermal2_Init();
int get_thermal2(void);

#endif