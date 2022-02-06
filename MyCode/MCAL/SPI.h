/*
 * SPI.h
 *
 * Created: 1/18/2022 3:38:09 PM
 *  Author: ahmed
 */ 


#ifndef SPI_H_
#define SPI_H_

#include "Config.h"

#define SPI_INT __vector_12

#define SPDR (*(volatile uint8*)(0x2F))
#define SPCR (*(volatile uint8*)(0x2D))
//interrupt enable,
//spi enable,
//data order(LSB first or MSB first)
//master/slave 0 master , 1 slave
//clock polarity CPOL
//clock phase CPHA

#define SPSR (*(volatile uint8*)(0x2E))
//interrupt flag
//Write Collision Flag
//Double SPI Speed Bit

#define SPI_MOSI P5
#define SPI_MISO P6
#define SPI_SCK P7
#define SPI_SS P4
#define SPI_FLAG P7
#define SPI_FLAG_COL P6
#define SPI_ORD P5

typedef enum{
	MASTER, SLAVE
}SPI_TYPE;
typedef enum{
	FOSC_4,
	FOSC_16,
	FOSC_64,
	FOSC_128
}SPI_PRESCALER;
typedef enum{
	SPI_NORMAL_SPEED,
	SPI_DOUBLE_SPEED
}SPI_SPEED_MODE;
typedef enum{
	SPI_SEND_MSB_FIRST,
	SPI_SEND_LSB_FIRST
}DATA_ORDER;
void SPI_INIT(SPI_TYPE t, DATA_ORDER order);
void SPI_ENABLE_INT();
void SPI_DISABLE_INT();
void SPI_SEND(uint8 data);
uint8 SPI_RECEIVE();
void SPI_CLOCK_INIT(SPI_PRESCALER scaler, SPI_SPEED_MODE mode);
#endif /* SPI_H_ */