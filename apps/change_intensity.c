#include "stm32f407xx.h"

#include "button_init.h"
#include "board_leds.h"
#include "timers.h"
#include "clocks.h"

int32_t x = 0;

int main() {
	usePLLClock();
	buttonInit();
	greenLedInit();
  
	SystemCoreClockUpdate();
	x = SystemCoreClock; // 75 MHz

	LedD15InitForTimer4();
	enableTim4();
	
	uint16_t intensities[4] = {0xF, 0xFF, 0xFFF, 0xFFFF};
	uint8_t crnt = 0;
	
	while(1){
		if(buttonPress()){
			crnt++;
			if (crnt > 3)
				crnt = 0;
			changeCCR4(intensities[crnt]);
		}
	}
}
