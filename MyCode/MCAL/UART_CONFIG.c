/*
 * UART_CONFIG.c
 *
 * Created: 1/18/2022 11:23:20 PM
 *  Author: ahmed
 */ 
#include "UART_CONFIG.h"

void (*TX_INT_FUN)(void) = myNULL;
void (*RX_INT_FUN)(void) = myNULL;

uint8* UART_Buffer;

void UART_TRANSMIT_STRING(uint8* str){
	uint8 idx = 0;
	while(str[idx] != '\0'){
		UART_TRANSMIT(str[idx], _8BIT_DATA);
		idx++;
	}
}
void UART_TRANSMIT_FRAME(uint8* data){
	uint8 len = 0;
	uint16 sum = 0;
	
	while(data[len] != '\0'){
		sum+=data[len];
		len++;
	}
	UART_TRANSMIT(len, _8BIT_DATA);
	
	for(uint8 i = 0; i < len; i++){
		UART_TRANSMIT(data[i], _8BIT_DATA);
	}
	UART_TRANSMIT(sum, _8BIT_DATA);
	UART_TRANSMIT((sum>>8), _8BIT_DATA);
}
uint8* UART_RECEIVE_STRING(){
	uint8 idx = -1;
	uint8* str = "";
	uint8 v;
	do{
		
		v = UART_RECEIVE(_8BIT_DATA);
		
		if(v != 0x0D && v != 0x0A){
			idx++;
			str[idx] = v;
		}else{
			LCD_SEND_DATA('O');
		}
	}while(v != 0X0D && idx != -1); //0x0d enter//0x0a
	str[idx] = '\0';
	return str;
}
uint8 UART_RECEIVE_WIFI(){
	uint8 check[100] = "\r\nOK\r\n";
	uint8 rec[100];
	uint8 idx = 0;
	rec[idx] = UART_RECEIVE(_8BIT_DATA);
	uint8 i = 0;
	while(i != 6){
		/*if(rec[idx] == check[idx]) LCD_SEND_DATA('o');
		else{
			LCD_SEND_DATA(rec[idx]);
			return 0;
		}
		idx++;
		rec[idx] = UART_RECEIVE(_8BIT_DATA);*/
		LCD_SEND_DATA(rec[idx]);
		i++;
		idx++;
		rec[idx] = UART_RECEIVE(_8BIT_DATA);
	}
	
	return 1;
}
uint8 UART_RECEIVE_FRAME(uint8* res){
	
	uint16 test = 0;
	uint8 num = UART_RECEIVE(_8BIT_DATA);//1
	uint8 data[num];//2
	for(uint8 i = 0; i < num; i++){
		data[i] = UART_RECEIVE(_8BIT_DATA);
		res[i] = data[i];
		test+=data[i];
	}
	uint16 checkSum = UART_RECEIVE(_8BIT_DATA);
	checkSum|=(UART_RECEIVE(_8BIT_DATA)<<8);//3
	if(test != checkSum) return 0;
	
	return 1;
}

uint8 UART_Frame_Cut(uint8* str1, uint8* str2, uint8 a, uint8 b){
	uint8 idx = 0;
	
	while(1){
		uint8 rec = UART_RECEIVE(_8BIT_DATA);
		if(rec == ',') break;
		str1[idx++] = rec;
	}
	str1[idx] = '\0';
	idx = 0;
	while(1){
		uint8 rec = UART_RECEIVE(_8BIT_DATA);
		if(rec == ',') break;
		str2[idx++] = rec;
	}
	str2[idx] = '\0';
	idx = 0;
	while(1){
		uint8 rec = UART_RECEIVE(_8BIT_DATA);
		if(rec == ',') break;
		a *= 10;
		a += (rec-'0');
	}
	while(1){
		uint8 rec = UART_RECEIVE(_8BIT_DATA);
		if(rec == 0x0d) break;
		b *= 10;
		b += (rec-'0');
	}
	LCD_SEND_STRING(str1);
	LCD_SEND_DATA(' ');
	LCD_SEND_STRING(str2);
	LCD_GOTO(second_row, col_0);
	LCD_SEND_INT(a);
	LCD_SEND_DATA(' ');
	LCD_SEND_INT(b);
}

void UART_TRANSMIT_STRING_ASYNCH(uint8* str){
	UART_Buffer = str;
	UDR = str[0];
	setCallBack_TX_INT(TX_FUN);
	UART_ENABLE(TX);
}
void setCallBack_TX_INT(void (*fun)(void)){
	TX_INT_FUN = fun;
}
void setCallBack_RX_INT(void (*fun)(void)){
	RX_INT_FUN = fun;
}
void TX_FUN(void){
	static uint8 idx = 1;
	if(UART_Buffer[idx]!='\0'){
		UDR = UART_Buffer[idx];
		idx++;
	}else{
		idx=1;
		UART_DISABLE(TX);
	}
}