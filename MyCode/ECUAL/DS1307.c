/*
 * DS1307.c
 *
 * Created: 1/29/2022 2:18:10 PM
 *  Author: ahmed
 */ 
#include "DS1307.h"

void RTCS_INIT(){
	I2C_START();
	while((TWSR & 0xF8) != I2C_START_CON);
	I2C_WRITE(RTCS_WRITE_ADDRESS);
	while((TWSR & 0xF8) != I2C_TR_SLA_W_ACK);
	I2C_WRITE(RTCS_COFIG_REG);
	while((TWSR & 0xF8) != I2C_TR_DATA_ACK);
	I2C_WRITE(0x00);
	while((TWSR & 0xF8) != I2C_TR_DATA_ACK);
	I2C_STOP();
}

void RTCS_SET_DATE(RTCS_DATE* set){
	I2C_START();
	while((TWSR & 0xF8) != I2C_START_CON);
	I2C_WRITE(RTCS_WRITE_ADDRESS);
	while((TWSR & 0xF8) != I2C_TR_SLA_W_ACK);
	I2C_WRITE(RTCS_SECONDS_REG);
	while((TWSR & 0xF8) != I2C_TR_DATA_ACK);
	
	I2C_WRITE(set->sec);
	while((TWSR & 0xF8) != I2C_TR_DATA_ACK);
	I2C_WRITE(set->min);
	while((TWSR & 0xF8) != I2C_TR_DATA_ACK);
	I2C_WRITE(set->hour);
	while((TWSR & 0xF8) != I2C_TR_DATA_ACK);
	I2C_WRITE(set->wday);
	while((TWSR & 0xF8) != I2C_TR_DATA_ACK);
	I2C_WRITE(set->day);
	while((TWSR & 0xF8) != I2C_TR_DATA_ACK);
	I2C_WRITE(set->month);
	while((TWSR & 0xF8) != I2C_TR_DATA_ACK);
	I2C_WRITE(set->year);
	while((TWSR & 0xF8) != I2C_TR_DATA_ACK);
	I2C_STOP();
}
void RTCS_READ_DATE(RTCS_DATE* get){
	I2C_START();
	while((TWSR & 0xF8) != I2C_START_CON);
	I2C_WRITE(RTCS_WRITE_ADDRESS);
	while((TWSR & 0xF8) != I2C_TR_SLA_W_ACK);
	I2C_WRITE(RTCS_SECONDS_REG);
	while((TWSR & 0xF8) != I2C_TR_DATA_ACK);
	I2C_STOP();
	
	I2C_START();
	while((TWSR & 0xF8) != I2C_START_CON);
	I2C_WRITE(RTCS_READ_ADDRESS);
	while((TWSR & 0xF8) != I2C_TR_SLA_R_ACK);
	
	get->sec = I2C_READ_ACK();
	get->min = I2C_READ_ACK();
	get->hour = I2C_READ_ACK();
	get->wday = I2C_READ_ACK();
	get->day = I2C_READ_ACK();
	get->month = I2C_READ_ACK();
	get->year = I2C_READ_ACK();
	I2C_STOP();
}
void RTCS_PRINT_TIME(RTCS_DATE* rtc){
	LCD_SEND_INT( (rtc->sec)>>4 );
	LCD_SEND_INT( (rtc->sec)&(0x0F) );
	LCD_SEND_DATA(':');
	
	LCD_SEND_INT( (rtc->min)>>4 );
	LCD_SEND_INT( (rtc->min)&(0x0F) );
	LCD_SEND_DATA(':');
	
	LCD_SEND_INT( (rtc->hour)>>4 );
	LCD_SEND_INT( (rtc->hour)&(0x0F) );
}
void RTCS_PRINT_DATE(RTCS_DATE* rtc){
	LCD_SEND_INT( (rtc->day)>>4 );
	LCD_SEND_INT( (rtc->day)&(0x0F) );
	LCD_SEND_DATA(':');
	
	LCD_SEND_INT( (rtc->month)>>4 );
	LCD_SEND_INT( (rtc->month)&(0x0F) );
	LCD_SEND_DATA(':');
	
	LCD_SEND_INT( (rtc->year)>>4 );
	LCD_SEND_INT( (rtc->year)&(0x0F) );
}