#ifndef SPI_H
#define SPI_H
#include "stm32f407xx.h"

void SpiConfig(void);
void SpiPinsConfig(void);
void SpiEnable(void);
void SpiDisable(void);
void SpiTransmit(uint8_t *data, uint8_t size);
void SpiReceive(uint8_t *data, uint8_t size);
void motionSensorRead(uint8_t address, uint8_t* data_output);
void motionSensorTransmit(uint8_t address, uint8_t value);

#endif