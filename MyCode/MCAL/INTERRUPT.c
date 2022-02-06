/*
 * INTERRUPT.c
 *
 * Created: 11/17/2021 5:49:26 PM
 *  Author: ahmed
 */ 
#include "interrupt.h"


/*void __vector_2(void) __attribute__((signal));
void __vector_2(void){
	
}*/
ISR(INT2){
	if(ISBITSET(*GIFR, P5)){
		TOGGLEBIT(GPIOA->PORT.data, P2);
		_delay_ms(3000);
	}
	else{
		TOGGLEBIT(GPIOA->PORT.data, P1);
		_delay_ms(3000);
	}
	
}
int flag = 0;
ISR(INT1){
	if(flag == 0){
		OCR1BH = 3;
		OCR1BL = 232;
		flag++;
	}
	if(flag == 1){
		OCR1BH = 5;
		OCR1BL = 220;
		flag++;
	}
	if(flag == 2){
		OCR1BH = 7;
		OCR1BL = 208;
		flag = 0;
	}
}
ISR(INT0){
	
	
	TOGGLEBIT(GPIOA->PORT.data, P0);
	/*static flag = 0;
	if(flag == 0){
		TCNT0 = 0;
		ENABLEINT(INT0_EXT, INT0_MODE_RISING);
		flag = 1;
		TOGGLEBIT(GPIOA->PORT.data, P0);
	}else{
		ENABLEINT(INT0_EXT, INT0_MODE_FALLING);
		flag = 0;
		TOGGLEBIT(GPIOA->PORT.data, P0);
	}*/
	
	
}


ISR(BAD_INT){
	TOGGLEBIT(GPIOA->PORT.data, P1);
}

void ENABLEINT(INTNAME n, INTMODE m){
	
	//critical section
	GID();
	switch(n){
		case INT0_EXT:
			*MCUCR = ((*MCUCR)&(0xFC)) | m;
			break;
		case INT1_EXT:
			*MCUCR = ((*MCUCR)&(0xF3)) | m;
			break;
		case INT2_EXT:
			*MCUCSR = ((*MCUCSR)&(0xBF)) | m;
			break;
		default:break;
			
	}
	*GICR |= (n);
	GIE();
}
void DISABLEINT(INTNAME n){
	*GICR &=~(n);
}
void SETCALLBACKINT(INTNAME INT, void (*ptrINT) (void)){
	switch(INT){
		case INT0_EXT:
			INT0_ptr = ptrINT;
			break;
		case INT1_EXT:
			INT1_ptr = ptrINT;
			break;
		case INT2_EXT:
			INT2_ptr = ptrINT;
			break;
		default:break;
	}
}