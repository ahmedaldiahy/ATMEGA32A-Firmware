/*
 * I2C_APP.c
 *
 * Created: 1/28/2022 6:42:59 PM
 *  Author: ahmed
 */ 
#include "LCD_I2C.h"

void I2C_LCD_INIT(uint8 address){
	
	I2C_LCD_SEND_INSTRUCTION(RETURN_HOME, address);
	I2C_LCD_SEND_INSTRUCTION(DISPLAY, address);
	I2C_LCD_SEND_INSTRUCTION(DATA_SET, address);
	I2C_LCD_SEND_INSTRUCTION(CLEAR_DISPLAY, address);
	
}
void I2C_LCD_READ(){
	I2C_WRITE(TWDR|=(0x02));
	while( (TWSR & (0xF8)) != I2C_TR_DATA_ACK);
	_delay_ms(1);
	I2C_WRITE(TWDR&=~(0x02));
	while( (TWSR & (0xF8)) != I2C_TR_DATA_ACK);
}
void I2C_LCD_SEND_INSTRUCTION(uint8 data, uint8 address){
	
	I2C_START();
	while( (TWSR & (0xF8)) != I2C_START_CON);
	I2C_WRITE(address);
	while( (TWSR & (0xF8)) != I2C_TR_SLA_W_ACK);
	I2C_WRITE(TWDR&=~(0x01));
	while( (TWSR & (0xF8)) != I2C_TR_DATA_ACK);
	I2C_WRITE(TWDR &= 0x0F);
	while( (TWSR & (0xF8)) != I2C_TR_DATA_ACK);
	I2C_WRITE(TWDR | (data&0xF0));
	while( (TWSR & (0xF8)) != I2C_TR_DATA_ACK);
	I2C_LCD_READ();

	I2C_WRITE(TWDR &= 0x0F);
	while( (TWSR & (0xF8)) != I2C_TR_DATA_ACK);
	I2C_WRITE(TWDR |= ((data & 0x0F)<<4));
	while( (TWSR & (0xF8)) != I2C_TR_DATA_ACK);
	I2C_LCD_READ();
	
	I2C_STOP();
}
void I2C_LCD_SEND_DATA(uint8 data, uint8 address){
	I2C_START();
	while( (TWSR & (0xF8)) != I2C_START_CON);
	I2C_WRITE(address);
	while( (TWSR & (0xF8)) != I2C_TR_SLA_W_ACK);
	I2C_WRITE(TWDR|=(0x01));
	while( (TWSR & (0xF8)) != I2C_TR_DATA_ACK);
	I2C_WRITE(TWDR &= 0x0F);
	while( (TWSR & (0xF8)) != I2C_TR_DATA_ACK);
	I2C_WRITE(TWDR | (data&0xF0));
	while( (TWSR & (0xF8)) != I2C_TR_DATA_ACK);
	I2C_LCD_READ();

	I2C_WRITE(TWDR &= 0x0F);
	while( (TWSR & (0xF8)) != I2C_TR_DATA_ACK);
	I2C_WRITE(TWDR |= ((data& 0x0F)<<4));
	while( (TWSR & (0xF8)) != I2C_TR_DATA_ACK);
	I2C_LCD_READ();
	
	I2C_STOP();
}
void I2C_LCD_SEND_STRING(uint8* data, uint8 address){
	uint8 idx = 0;
	while(data[idx] != '\0'){
		I2C_LCD_SEND_DATA(data[idx], address);
		idx++;
	}
}