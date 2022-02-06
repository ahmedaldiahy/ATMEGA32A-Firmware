/*
 * ULTRA_SONIC.c
 *
 * Created: 12/20/2021 4:42:17 PM
 *  Author: ahmed
 */ 
#include "ULTRA_SONIC.h"

uint32 ultra_flag, start, end, ovf, ret;
ISR(Timer1_OVF){
	
	if(ovf == 3) ovf = 0;
	ovf++;
}
ISR(Timer1_ICF){
	
		if(ultra_flag == 0){
			ovf = 0;
			start = ICU1;
			ultra_flag = 1;
			INPUT_CAPTURE_CONFIG(ICP_FALLING);
		}
		else{
			end = ICU1;
			ultra_flag = 2;
			INPUT_CAPTURE_CONFIG(ICP_RISING);
		}
}
uint32 START_ULTRA(void){
	
	ultra_flag = 0;
	TCNT1(0);
	ENABLE_TIMER1(PRESCALAR_8);
	INPUT_CAPTURE_CONFIG(ICP_RISING);
	ENABLE_TIMER1_INT(TIMER1_ICU_INT);
	ENABLE_TIMER1_INT(TIMER1_OVF_INT);
	
	SETBIT(Trig_ultra_OUT, Trig_ultra_PIN);
	_delay_us(50);
	CLEARBIT(Trig_ultra_OUT, Trig_ultra_PIN);
	
	while(ultra_flag < 2);
	
	STOP_TIMER1();
	DISABLE_TIMER1_INT(TIMER1_ICU_INT);
	DISABLE_TIMER1_INT(TIMER1_OVF_INT);
	//return (sint32)( ( (end-start) + ( (sint32)ovf*(65535) ) )/58);
	ret = (end-start) + ((uint32)ovf*65535);
	ret*=8;
	return ret/58;
}
