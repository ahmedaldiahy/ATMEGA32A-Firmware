/*
 * LM35.c
 *
 * Created: 12/28/2021 12:11:15 AM
 *  Author: ahmed
 */ 
#include "Config.h"
	
		/*  
			ADC_Resolution = (volatage ref/1024)
			vout = ADC_Resolution*ADC_out
			temperature = vout/10mv;
			
			10mv for each degree c
		*/


uint32 LM35_Conversion(uint32 vout){
	
	float32 f = vout;
	f *= (float32)(5)/1024;
	f/= .01;
	return f;
}