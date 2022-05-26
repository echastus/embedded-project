#include "clocks.h"

uint32_t SystemClock(void){
	SystemCoreClockUpdate();
	return SystemCoreClock;
}

void usePLLClock(void) {
	// start HSE
	RCC->CR |= RCC_CR_HSEON;
	
	// use HSE for PLL
	RCC->PLLCFGR |= RCC_PLLCFGR_PLLSRC_HSE;
	
	// set pllp divide by 2 (default)
	RCC ->PLLCFGR &= ~RCC_PLLCFGR_PLLP_Msk;
	
	// set division factor to 4
	RCC ->PLLCFGR &= ~RCC_PLLCFGR_PLLM_Msk;
	RCC->PLLCFGR |= 4U << RCC_PLLCFGR_PLLM_Pos;
	
	// set multiplication factor to 48
	RCC ->PLLCFGR &= ~RCC_PLLCFGR_PLLN_Msk;
	RCC->PLLCFGR |= 24U << RCC_PLLCFGR_PLLN_Pos;
	
	// switch to PLL as main clock
	FLASH->ACR |= 5; // IMPORTANT FOR HIGH VALUE PLLs!!!: flash delay
  RCC->CFGR &= ~RCC_CFGR_SW;
	RCC->CFGR |= RCC_CFGR_SW_PLL;
	
	// start PLL
	RCC->CR |= RCC_CR_PLLON;
	while (!(RCC->CR & RCC_CR_PLLRDY));
	
	// disable HSI
	RCC->CR &= ~RCC_CR_HSION;
	
	//result is 75 MHz
}

void sysTickInit(void) {
	//The SysTick calibration value is fixed to 18750, which gives a reference time base of 1 ms 
  //with the SysTick clock set to 18.75 MHz (HCLK/8, with HCLK set to 150 MHz).
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
}

void enableTim4(void) {
	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;		//enable Tim4 TIM4
	TIM4->CR1 |= TIM_CR1_CEN;
	TIM4->CCMR2 |= TIM_CCMR2_OC4CE;
	TIM4->CCMR2 |= 6UL << TIM_CCMR2_OC4M_Pos;
	TIM4->ARR = 0b11101010010111; // 14999
	TIM4->PSC = 1000UL-1UL;
	TIM4->CCR4 = 0xF;
	// When you press the blue button, the actual CNT value is saved in CCR1 register 
	// giving you the precise moment the falling edge occurs. 
	// This is the very basic functionality of Input Capture mode.
	TIM4->CCER |= TIM_CCER_CC4E;
}

void changeCCR4(uint16_t new_ccr4_val) {
	TIM4->CCR4 = new_ccr4_val;	
}
