#include "spi.h"

// indicates that the buffer is empty
#define SPI1_TXE ((SPI1->SR)&(1 << 1))
// indicates that SPI is not busy
#define SPI1_BSY ((SPI1->SR)&(1 << 7))
// indicates that RX buffer is not empty
#define SPI1_RXNE ((SPI1->SR)&(1 << 0))

void SpiConfig(void) {
	// enable SPI1 clk
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
	// master mode
	SPI1->CR1 |= SPI_CR1_MSTR | SPI_CR1_SSI | SPI_CR1_SSM;
	// baud rate, fPCLK/8
	SPI1->CR1 |= 0x2 << SPI_CR1_BR_Pos;
	// 8 bit data size
	SPI1->CR1 &= ~(SPI_CR1_DFF);
	// enable SPI1
	SPI1->CR1 |= SPI_CR1_SPE;
}

void SpiPinsConfig(void) {
	// enable GPIOA clock
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;
	
	//PE3 -> CS
	//PA5 -> SCL/SPC
	//PA6 -> SDO / MISO
	//PA7 -> SDA/SDI/SDO / MOSI
	
	//configure pins
	GPIOA->MODER &= ~(GPIO_MODER_MODER5 | GPIO_MODER_MODER6 | GPIO_MODER_MODER7);
	GPIOA->MODER |= (2 << 10U | 2 << 12U | 2 << 14U); // af mode
	GPIOA->AFR[0] |= (5 << 20U)|(5 << 24U )|(5 << 28U);   // AF5(SPI1) for PA5, PA6, PA7
	
	GPIOE->MODER |= (1 << 6U); // output for PA3
}

void SpiEnable(void) {
	SPI1->CR1 |= SPI_CR1_SPE;   // SPE=1, Peripheral enabled
}

void SpiDisable(void) {
	SPI1->CR1 &= ~(SPI_CR1_SPE);   // SPE=0, Peripheral Disabled
}

void SpiCSEnable(void){
	GPIOE->BSRR |= (1 << 3U) << 16U;
}

void SpiCSDisable(void) {
	GPIOE->BSRR |= (1 << 3U);
}

void SpiTransmit(uint8_t *data, uint8_t size) {
	uint8_t i = 0;
	while(i < size) {
		while(!SPI1_TXE){};
		SPI1->DR = data[i];
		i++;
	}
	
		uint8_t temp = SPI1->DR;
					  temp = SPI1->SR;

	while(!SPI1_TXE){};
	while(SPI1_BSY){};
	}
	
void SpiReceive(uint8_t *data, uint8_t size) {
	while(size) {
		while(SPI1_BSY){}; //wait till SPI is not busy
		SPI1->DR = 0;  // send dummy data
		while(!SPI1_RXNE){};
		*data++ = (SPI1->DR);
		size--;
	}
}

void motionSensorTransmit(uint8_t address, uint8_t value) {
	uint8_t data[2] = {address, value};
	// begin transaction with CS changing high to low
	SpiCSEnable();
	SpiTransmit(data, 2);
	SpiCSDisable();
}

void motionSensorRead(uint8_t address, uint8_t* data_output) {
	address |= 0x80; // read byte
	uint8_t data[1] = {address};
	// begin transaction with CS changing high to low
	SpiCSEnable();
	SpiTransmit(data, 1);
	SpiReceive(data_output, 1);
	SpiCSDisable();
}









