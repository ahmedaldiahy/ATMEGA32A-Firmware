/*
 * UART_CONFIG.h
 *
 * Created: 1/18/2022 11:23:33 PM
 *  Author: ahmed
 */ 


#ifndef UART_CONFIG_H_
#define UART_CONFIG_H_

#include "Config.h"



void UART_TRANSMIT_STRING(uint8* str);
void UART_TRANSMIT_FRAME(uint8*);

uint8* UART_RECEIVE_STRING();
uint8 UART_RECEIVE_FRAME(uint8*);
uint8 UART_Frame_Cut(uint8*, uint8*, uint8, uint8);

uint8 UART_RECEIVE_WIFI();

void setCallBack_TX_INT(void (*fun)(void));
void setCallBack_RX_INT(void (*fun)(void));

void UART_TRANSMIT_STRING_ASYNCH(uint8* str);
void TX_FUN(void);
#endif /* UART_CONFIG_H_ */