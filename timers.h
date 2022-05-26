#ifndef TIMERS_H
#define TIMERS_H
#include "stm32f407xx.h"

void additiveDelay(uint32_t max_cnt);


void SysTick_delay(int delay_amount);
void SysTick_Handler(void);


#endif



