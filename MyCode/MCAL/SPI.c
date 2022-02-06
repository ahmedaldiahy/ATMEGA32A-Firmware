/*
 * SPI.c
 *
 * Created: 1/18/2022 3:37:58 PM
 *  Author: ahmed
 */ 
#include "SPI.h"

ISR(SPI_INT){
	
}
void SPI_INIT(SPI_TYPE t, DATA_ORDER order){
	SETBIT(SPCR, P6);
	switch(t){
		
		case MASTER:
			SETBIT(SPCR, P4);
			DIR(GPIOB->DDR.data, OUTPUT, SPI_MOSI);
			DIR(GPIOB->DDR.data, OUTPUT, SPI_SCK);
			DIR(GPIOB->DDR.data, OUTPUT, SPI_SS);
			break;
		case SLAVE:
			DIR(GPIOB->DDR.data, INPUTPULLUP, SPI_MISO);
			DIR(GPIOB->DDR.data, INPUTPULLUP, SPI_SS);
			break;
	}
	if(order == SPI_SEND_MSB_FIRST) CLEARBIT(SPCR, SPI_ORD);
	if(order == SPI_SEND_LSB_FIRST) SETBIT(SPCR, SPI_ORD);
}
void SPI_CLOCK_INIT(SPI_PRESCALER scaler, SPI_SPEED_MODE mode){
	SPCR &= (0xFC);
	SPCR |= (scaler);
	
	SPSR &= (0xFE);
	SPSR |= (mode);
}
void SPI_SEND(uint8 data){
	OUT(GPIOB->PORT.data, SPI_SS, LOW);
	SPDR = data;
	while(ISBITCLEAR(SPSR, SPI_FLAG));
}
uint8 SPI_RECEIVE(){
	while(ISBITCLEAR(SPSR, SPI_FLAG));
	return SPDR;
}
void SPI_ENABLE_INT(){
	SETBIT(SPCR, P7);
}
void SPI_DISABLE_INT(){
	CLEARBIT(SPCR, P7);
}