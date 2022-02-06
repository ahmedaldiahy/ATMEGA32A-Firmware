/*
 * LCD.c
 *
 * Created: 12/16/2021 10:26:18 PM
 *  Author: ahmed
 */ 
#include "LCD.h"

void LCD_init(void){
	
	SETBIT(DIR_control, E);
	SETBIT(DIR_control, RS);
	SETBIT(DIR_control, RW);
	
	#if eight_bitdata
		DIR_data = 0xFF;	
	#else
		#if upper_bits_four_bitdata
			DIR_data |= 0xF0;
		#else
			DIR_data |= 0x0F;
		#endif
		LCD_SEND_INSTRUCTION(RETURN_HOME);
	#endif
	
	LCD_SEND_INSTRUCTION(DISPLAY);
	LCD_SEND_INSTRUCTION(DATA_SET);
	LCD_SEND_INSTRUCTION(CLEAR_DISPLAY);
	
	
}
void LCD_SEND_INSTRUCTION(uint8 data){
	CLEARBIT(OUT_control, RS);
	CLEARBIT(OUT_control, RW);
	_delay_ms(1);

	#if eight_bitdata
		SETBIT(OUT_control, E);
		_delay_ms(1);
		OUT_data = data;
		_delay_ms(1);
		CLEARBIT(OUT_control, E);
	#else
		#if upper_bits_four_bitdata
			SETBIT(OUT_control, E);
			_delay_ms(1);
			OUT_data &= (0x0F);
			OUT_data |= (data&(0xF0));
			_delay_ms(1);
			CLEARBIT(OUT_control, E);
			_delay_ms(1);
			
			SETBIT(OUT_control, E);
			_delay_ms(1);
			OUT_data &= (0x0F);
			OUT_data |= (data<<4);
			_delay_ms(1);
			CLEARBIT(OUT_control, E);
		#else
			SETBIT(OUT_control, E);
			_delay_ms(1);
			OUT_data &= (0xF0);
			OUT_data |= (data>>4);
			_delay_ms(1);
			CLEARBIT(OUT_control, E);
			_delay_ms(1);
			
			SETBIT(OUT_control, E);
			_delay_ms(1);
			OUT_data &= (0xF0);
			OUT_data |= (data & (0x0F));
			_delay_ms(1);
			CLEARBIT(OUT_control, E);
			_delay_ms(1);
		#endif
	#endif
		
}
void LCD_SEND_DATA(uint8 data){
	SETBIT(OUT_control, RS);
	CLEARBIT(OUT_control, RW);
	_delay_ms(1);
	
	#if eight_bitdata
		SETBIT(OUT_control, E);
		_delay_ms(1);
		OUT_data = data;
		_delay_ms(1);
		CLEARBIT(OUT_control, E);
		_delay_ms(1);
	
	#else 
		#if upper_bits_four_bitdata
			SETBIT(OUT_control, E);
			_delay_ms(1);
			OUT_data &= (0x0F);
			OUT_data |= (data & (0xF0));
			_delay_ms(1);
			CLEARBIT(OUT_control, E);
			_delay_ms(1);
			
			SETBIT(OUT_control, E);
			_delay_ms(1);
			OUT_data &= (0x0F);
			OUT_data |= (data<<4);
			_delay_ms(1);
			CLEARBIT(OUT_control, E);
			_delay_ms(1);
		#else
			SETBIT(OUT_control, E);
			_delay_ms(1);
			OUT_data &= (0xF0);
			OUT_data |= (data>>4);
			_delay_ms(1);
			CLEARBIT(OUT_control, E);
			_delay_ms(1);
			
			SETBIT(OUT_control, E);
			_delay_ms(1);
			OUT_data &= (0xF0);
			OUT_data |= (data & (0x0F));
			_delay_ms(1);
			CLEARBIT(OUT_control, E);
			_delay_ms(1);
		#endif
	
	#endif
	
	
}
void LCD_SEND_STRING(uint8* str){
	uint8 idx = 0;
	while(str[idx]!='\0'){
		LCD_SEND_DATA(str[idx++]);
	}
}
void LCD_SEND_INT(uint32 n){
	char str[20];
	ltoa(n, str, 10);
	LCD_SEND_STRING(str);
	
	
	/*char c[100];
	uint8 idx = 0;
	while(n){
		c[idx++] = '0' + (n%10);
		n/=10;
	}
	for(int i = idx-1; i >= 0; i--) LCD_SEND_DATA(c[i]);*/
	
}
void LCD_CLEAR(){
	LCD_SEND_INSTRUCTION(CLEAR_DISPLAY);
}
void LCD_GOTO(row row, col col){
	uint8 go_to = row+col;
	LCD_SEND_INSTRUCTION(DDRAM|go_to);
	
}
void LCD_DRAW_CHAR(uint8* data){
	//uint8 x[] = {0x0E, 0x08, 0x1E, 0x00, 0x04, 0x04, 0x04, 0x04}; '?'
	static uint8 idx = 0;
	uint8 address = idx*8;
	LCD_SEND_INSTRUCTION(CGRAM|address);
	
	for(uint8 i = 0; i < 8; i++){
		LCD_SEND_DATA(data[i]);
	}
	LCD_SEND_INSTRUCTION(DDRAM);
	LCD_SEND_DATA(idx);
	idx++;
}