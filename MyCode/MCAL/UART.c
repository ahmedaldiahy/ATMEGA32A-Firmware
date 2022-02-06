/*
 * UART.c
 *
 * Created: 1/2/2022 3:18:29 PM
 *  Author: ahmed
 */ 
#include "UART.h"

uint8 idx = 0;
uint8 data[100];
ISR(RX_INT){
	
	data[idx++] = UDR;
	SETBIT(GPIOD->DDR.data, P7);
	SETBIT(GPIOD->PORT.data, P7);
	LCD_SEND_INT(idx);
}
void UART_INTERRUPT_ENABLE(UART_INTERRUPT INT){
	switch(INT){
		case RX_INTERRUPT:
			SETBIT(UCSRB, P7);
			break;
		case TX_INTERRUPT:
			SETBIT(UCSRB, P6);
			break;
		case UDR_INTERRUPT:
			SETBIT(UCSRB, P5);
			break;
		default:break;
	}
}
void UART_INTERRUPT_DISABLE(UART_INTERRUPT INT){
	switch(INT){
		case RX_INTERRUPT:
			CLEARBIT(UCSRB, P7);
			break;
		case TX_INTERRUPT:
			CLEARBIT(UCSRB, P6);
			break;
		case UDR_INTERRUPT:
			CLEARBIT(UCSRB, P5);
			break;
		default:break;
	}
}

void UART_ENABLE(UART_COM com){
	UCSRB |= (1<<(3+com));
}
void UART_DISABLE(UART_COM com){
	UCSRB &= ~(1<<(3+com));
}

void UART_init(UART_SPEED _speed, UART_FRAME_SIZE _size, UART_PARITY _parity, UART_STOP_BIT _stop, UART_MODE _mode, UART_BAUD_RATE _baud){
	
	//baud rate
	uint8 x = 16;
	if(_speed == DOUBLE_SPEED) x = 8;
	UBRR((F_CPU / ((unsigned long)(_baud)*x)) - 1);
	UCSRA |= (_speed<<1);
	UCSRC |= (1<<7)|(_stop<<3)|(_parity<<4)|(_mode<<6);
	
	//frame size
	UCSRC |= (1<<7)|( (0x03 & _size) << 1 );
	UCSRB |= (0x04 & _size);

}
void UART_TRANSMIT(uint16 data, UART_FRAME_SIZE _size){
	while(ISBITCLEAR(UCSRA, P5));
	if(_size == _9BIT_DATA){
		UCSRB |= (data<<8);
	}
	UDR = data;
}
uint16 UART_RECEIVE(UART_FRAME_SIZE _size){
	while(ISBITCLEAR(UCSRA, P7));
	uint16 data = 0;
	if(_size == _9BIT_DATA){
		data |= (ISBITSET(UCSRB, P1));
		data<<=8;
	}
	data|=UDR;
	return data;
}
uint16 UART_RECEIVE_NO_BLOCK(UART_FRAME_SIZE _size, uint16 *ptr){
	uint16 data = 0;
	if(ISBITSET(UCSRA, P7)){
		if(_size == _9BIT_DATA){
			data |= ( (ISBITSET(UCSRB, P1)) << 8);
		}
		data |= UDR;
		*ptr = data;
		return 1;
	}
	return 0;
}