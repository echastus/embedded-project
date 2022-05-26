#ifndef CLOCKS_H
#define CLOCKS_H

#include "stm32f407xx.h"

uint32_t SystemClock(void);

void usePLLClock(void);
void sysTickInit(void);
void enableTim4(void);
void changeCCR4(uint16_t new_ccr4_val);

#endif
