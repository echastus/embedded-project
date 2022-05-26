#include "stm32f407xx.h"
#include "stdio.h"

#include "button_init.h"
#include "board_leds.h"
#include "timers.h"
#include "clocks.h"
#include "spi.h"
#include "lis302dl.h"

int32_t sys_clk = 0;
uint8_t data[4] = {0, 0, 0, 0};

int main() {
	//usePLLClock();

	SystemCoreClockUpdate();
	sys_clk = SystemCoreClock; // 75 MHz
	
	SpiPinsConfig();
	SpiConfig();
	
	greenLedInit();
	LedD15InitForTimer4();
	enableTim4();
	
	//enable x y z axis, enabled by default anyway
	motionSensorTransmit(0x20, 0x7);
	while(1){
		additiveDelay(2000);
		motionSensorRead(LIS302_REG_OUT_X, &data[0]);
		motionSensorRead(LIS302_REG_OUT_Y, &data[1]);
		motionSensorRead(LIS302_REG_OUT_Z, &data[2]);
		printf("X: %i Y: %i Z: %i\r\n", data[0], data[1], data[2]);
		changeCCR4(999);
	}
}
