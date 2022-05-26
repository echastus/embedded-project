#include "button_init.h"
#include "board_leds.h"
#include "timers.h"

void buttonPressGreen(void) {
	while(GPIOA->IDR & GPIO_IDR_ID0){
		greenLedToggle();
	}
	additiveDelay(500);
}

uint8_t buttonPress(void) {
		while(GPIOA->IDR & GPIO_IDR_ID0){
			additiveDelay(1000);
			return 1;
		}
		additiveDelay(1000);
		return 0;
}

void buttonInit(void) {
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD0; // no pull up/down
	GPIOA->MODER &= ~GPIO_MODER_MODER0; // input (reset state for PA0, user button)
}
