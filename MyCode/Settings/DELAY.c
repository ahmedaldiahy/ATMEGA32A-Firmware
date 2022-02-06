/*
 * DELAY.c
 *
 * Created: 1/3/2022 4:36:44 PM
 *  Author: ahmed
 */ 
#include "DELAY.h"

void delay_micro(uint32 x){
	for(uint32 i = (F_CPU/1000000)*x/30; i > 0; i--){
		__asm("NOP");
	}
}
void delay_mili(uint32 x) {
	for(uint32 i = (F_CPU/1000)*x/30; i > 0; i--){
		__asm("NOP");
	}
}