/*
 * ADC.c
 *
 * Created: 12/27/2021 8:46:02 PM
 *  Author: ahmed
 */ 
#include "ADC.h"

ISR(ADC_INT){
	uint32 res = 0;
	res = ADCL;
	res|=(ADCH<<8);
	LCD_CLEAR();
	LCD_SEND_INT(LM35_Conversion(res));
}
void ADC_init(ADC_PRESCALAR scaler, ADC_REF ref, ADCchannel channel, TriggerSource src){
	
	
	
	ADCSRA|=(1<<P7);// enable ADC
	
	//prescaler
	ADCSRA&=0xF8;
	ADCSRA|=scaler;
	
	//voltage reference 
	ADMUX &=0x3F;
	ADMUX |= ref;
	
	//select channel
	ADMUX&= 0xE0;
	ADMUX |=channel;
	
	if(src != Single_Conversion){
		SETBIT(ADCSRA, P5);
		SFIOR &= (0x1F);
		SFIOR |= src;
	}
	
	
	
}
uint32 ADC_StartConversion(ADC_ADJUST adj){
	
	
	//select adjustment
	ADMUX&=(0xDF);
	ADMUX|=(adj);
	
	//start conversion
	SETBIT(ADCSRA, P6);
	
	//while(ISBITCLEAR(ADCSRA, P4));
	while(ISBITSET(ADCSRA, P6));
	uint32 res = 0;
	
	switch(adj){
		case ADCL_8bit:
			res = ADCL;
			res|=(ADCH<<8);
			break;
		case ADCH_8bit:
			res = (ADCL>>6);
			res |= (ADCH<<2);
			break;
		default:break;
	}
	ADCSRA|=(1<<4);
	return res;
}

float32 ADC_Vout(uint32 adc_out){
	return (float32)(adc_out) * ((float32)5/1024);
}


