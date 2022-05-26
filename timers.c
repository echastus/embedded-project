#include "timers.h"

int msTicks = 0;

void additiveDelay(uint32_t max_cnt) {
	uint32_t cnt = 0;
	while (cnt < max_cnt) {
		cnt++;
	}
}

void SysTick_delay(int delay_amount){
	msTicks = 0;
	while(msTicks<delay_amount);
}

void SysTick_Handler(void){
	msTicks++;
}

