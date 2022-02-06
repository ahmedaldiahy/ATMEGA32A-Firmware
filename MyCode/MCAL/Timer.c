/*
 * Timer.c
 *
 * Created: 11/27/2021 6:09:16 PM
 *  Author: ahmed
 */ 
#include "Timer.h"

volatile uint8 temp = 0;
volatile uint8 mili = 0;

ISR(Timer0_OVF){
	
	/*TCNT0 = 56;
	if(temp == 4){
		SETBIT(GPIOB->PORT.data, P7);
		temp = 0;
	}else{
		CLEARBIT(GPIOB->PORT.data, P7);
		temp++;
	}*/
	
	TOGGLEBIT(GPIOB->PORT.data, P7);
	
}
ISR(Timer0_OCF){
	
}

ISR(Timer1_OCFB){
	
}

void INIT_TIMER0(TIMER0MODE mode, CLOCKTIMERSEL clk, INTTIMER0SEL in, OC0_ACTION oc0){
	
	//clock select
	TCCR0 &= 0xF8;
	TCCR0|=clk;
	
	//mode select
	TCCR0 &= 0xB7;
	TCCR0 |= mode;
	
	//int select
	TIMSK &= 0xFC;
	TIMSK|=in;
	
	//OC0_ACTION
	TCCR0 &= 0xCF;
	TCCR0 |= oc0;
	//if we didnt put a value in OCR0 it consider it as zero
	//the action happens in the next cycle //clear the counter TCNT0(in CTC) and toggle the pin OC0
	
}

void INIT_TIMER1(TIMER1MODE mode, CLOCKTIMERSEL clk, INTTIMER1SEL in, OC1A_ACTION oc1a, OC1B_ACTION oc1b){
	//mode 1
	TCCR1A &= (0xFC);
	TCCR1A |= (mode & 0X0F);
	//mode2
	TCCR1B &= (0xE7);
	mode = ((mode>>4)<<3);
	TCCR1B |= mode;
	
	//INT SEl
	TIMSK &= (0xC3);
	TIMSK|=in;
	
	//CLK SEL
	TCCR1B &= (0xF8);
	TCCR1B |= clk;
	
	//OC1A SEL
	
	TCCR1A &= (0x3F);
	TCCR1A |= oc1a;
	
	//OC1B SEL
	TCCR1A &= (0xCF);
	TCCR1A |= oc1b;
	
}
void INPUT_CAPTURE_CONFIG(INPUTCAPTURE_MODE mode){
	TCCR1B &= (0xBF);
	TCCR1B |= (mode);
}
void ENABLE_TIMER1_INT(INTTIMER1SEL in){
	switch (in){
		case TIMER1_OVF_INT:
			SETBIT(TIMSK, P2);
			break;
		case TIMER1_CMPB_INT:
			SETBIT(TIMSK, P3);
			break;
		case TIMER1_CMPA_INT:
			SETBIT(TIMSK, P4);
			break;
		case TIMER1_ICU_INT:
			SETBIT(TIMSK, P5);
			break;
		default:break;
	}
}
void DISABLE_TIMER1_INT(INTTIMER1SEL in){
	switch (in){
		case TIMER1_OVF_INT:
			CLEARBIT(TIMSK, P2);
			break;
		case TIMER1_CMPB_INT:
			CLEARBIT(TIMSK, P3);
			break;
		case TIMER1_CMPA_INT:
			CLEARBIT(TIMSK, P4);
			break;
		case TIMER1_ICU_INT:
			CLEARBIT(TIMSK, P5);
			break;
		default:break;
	}
}


void ENABLE_TIMER0(CLOCKTIMERSEL clk){
	TCCR0 &= 0xF8;
	TCCR0 |= clk;
}
void STOP_TIMER0(void){
	TCCR0 &= 0xF8;
}
void ENABLE_TIMER1(CLOCKTIMERSEL clk){
	TCCR1B &= (0xF8);
	TCCR1B |= clk;
}
void STOP_TIMER1(void){
	TCCR1B &= (0xF8);
}