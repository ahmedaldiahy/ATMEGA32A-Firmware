/*
 * EXTERNAL_EEPROM.c
 *
 * Created: 1/31/2022 4:21:27 PM
 *  Author: ahmed
 */ 
#include "24LC256.h"
void external_EEPROM_WRITE(uint16 address, uint8 data){
	I2C_START();
	while((TWSR & 0xF8) != (I2C_START_CON));
	I2C_WRITE(_24LC256_address_WRITE);
	while((TWSR & 0xF8) != (I2C_TR_SLA_W_ACK));
	I2C_WRITE(address>>8);
	while((TWSR & 0xF8) != (I2C_TR_DATA_ACK));
	I2C_WRITE((uint8)address);
	while((TWSR & 0xF8) != (I2C_TR_DATA_ACK));
	I2C_WRITE(data);
	while((TWSR & 0xF8) != (I2C_TR_DATA_ACK));
	I2C_STOP();
}
uint8 external_EEPROM_READ(uint16 address){
	uint8 data = 0;
	I2C_START();
	while((TWSR & 0xF8) != (I2C_START_CON));
	I2C_WRITE(_24LC256_address_WRITE);
	while((TWSR & 0xF8) != (I2C_TR_SLA_W_ACK));
	I2C_WRITE(address>>8);
	while((TWSR & 0xF8) != (I2C_TR_DATA_ACK));
	I2C_WRITE((uint8)address);
	while((TWSR & 0xF8) != (I2C_TR_DATA_ACK));
	
	I2C_STOP();
	
	I2C_START();
	while((TWSR & 0xF8) != (I2C_START_CON));
	I2C_WRITE(_24LC256_address_READ);
	while((TWSR & 0xF8) != (I2C_TR_SLA_R_ACK));
	data = I2C_READ_ACK();
	while((TWSR & 0xF8) != (I2C_REC_DATA_ACK));
	
	I2C_STOP();
	return data;
}
