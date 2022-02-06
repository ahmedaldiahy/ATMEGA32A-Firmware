/*
 * UART.h
 *
 * Created: 1/2/2022 3:18:40 PM
 *  Author: ahmed
 */ 


#ifndef UART_H_
#define UART_H_

#include "Config.h"

#define UCSRA (*(volatile uint8*)(0x2B))
//rxc, txc, UDRE, FE, DOR, PE, U2X, MPCM
#define UCSRB (*(volatile uint8*)(0x2A))
//RXIE, TXIE, UDRIE, RXEN, TXEN, UCSZ2,RXB9, TXB9
#define UCSRC (*(volatile uint8*)(0x40))
//URSEL, UMSEL, UPM1, UMP2, Stop bits, UCSZ1:0, clocl parity
#define UBRRL (*(volatile uint8*)(0x29))
#define UBRRH (*(volatile uint8*)(0x40))
#define UDR (*(volatile uint8*)(0x2C))

#define UBRR(baudRate)do{\
	UBRRH = ((baudRate) >> 8);\
	UBRRL = (uint8)(baudRate);\
	}while(0);
	
#define RX_INT __vector_13
#define UDR_INT __vector_14
#define TX_INT __vector_15

typedef enum{
	NORMAL_SPEED,
	DOUBLE_SPEED
}UART_SPEED;

typedef enum{
	TX, RX	
}UART_COM;

typedef enum{
	_5BIT_DATA,
	_6BIT_DATA,
	_7BIT_DATA,
	_8BIT_DATA,
	_9BIT_DATA = 0x07
}UART_FRAME_SIZE;

typedef enum{
	ASYNCHRONOUS, SYNCHRONOUS
}UART_MODE;

typedef enum{
	PARITY_DISABLE, 
	PARITY_EVEN = 0x02,
	PARITY_ODD
}UART_PARITY;

typedef enum{
	_1_STOP_BIT, _2_STOP_BIT
}UART_STOP_BIT;

typedef enum{
	_9600_RATE = 9600,
	_115200_RATE = 115200
}UART_BAUD_RATE;

typedef enum{
	TX_INTERRUPT, RX_INTERRUPT, UDR_INTERRUPT
}UART_INTERRUPT;

void UART_ENABLE(UART_COM com);
void UART_DISABLE(UART_COM com);
void UART_INTERRUPT_ENABLE(UART_INTERRUPT INT);
void UART_INTERRUPT_DISABLE(UART_INTERRUPT INT);

void UART_init(UART_SPEED _speed, UART_FRAME_SIZE _size, UART_PARITY _parity, UART_STOP_BIT _stop, UART_MODE _mode, UART_BAUD_RATE _baud);
void UART_TRANSMIT(uint16 data, UART_FRAME_SIZE _size);
uint16 UART_RECEIVE(UART_FRAME_SIZE _size);
uint16 UART_RECEIVE_NO_BLOCK(UART_FRAME_SIZE _size, uint16 *ptr);


#endif /* UART_H_ */