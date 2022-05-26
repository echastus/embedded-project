#include "board_leds.h"

// DISCOVERY HAS LEDS:
// from PD12 to PD14
void greenLedInit(void) {
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
	GPIOD->MODER &= ~GPIO_MODER_MODE12_Msk; // MASK MODER FOR PORT 12 D
	GPIOD->MODER |= 0x01 << GPIO_MODER_MODE12_Pos; // set port 12 D as general output
	
	GPIOD->BSRR = GPIO_BSRR_BR_12; // init state off
}

void LedD15InitForTimer4(void) {
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;	//enable GPIOD
	GPIOD->MODER |= 2UL << GPIO_MODER_MODE15_Pos;
	GPIOD->AFR[1] |= 2UL << GPIO_AFRH_AFSEL15_Pos;

	GPIOD->BSRR = GPIO_BSRR_BR_15; // init state off
}

void greenLedToggle(void) {
	GPIOD->ODR ^= GPIO_ODR_OD12;
}
