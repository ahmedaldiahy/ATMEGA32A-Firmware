/*
 * ADC.h
 *
 * Created: 12/27/2021 8:46:14 PM
 *  Author: ahmed
 */ 


#ifndef ADC_H_
#define ADC_H_

#include "Config.h"

#define ADMUX (*(volatile uint8*)(0x27))
//ref1, ref0, adjust, channel
#define ADCSRA (*(volatile uint8*)(0x26))
//ADCE, ADCS, auto trigger, ADC flag interrupt, ADC enable interrupt, ADC Prescaler
#define ADCH (*(volatile uint8*)(0x25))
#define ADCL (*(volatile uint8*)(0x24))
#define SFIOR (*(volatile uint8*)(0x50))
#define ADC_INT __vector_16
typedef enum{
	CH0,
	CH1,
	CH2,
	CH3, 
	CH4,
	CH5,
	CH6,
	CH7,
}ADCchannel;

typedef enum{
	ADC_PRESCALAR_2,
	ADC_PRESCALAR_2_2,
	ADC_PRESCALAR_4,
	ADC_PRESCALAR_8,
	ADC_PRESCALAR_16,
	ADC_PRESCALAR_32,
	ADC_PRESCALAR_64,
	ADC_PRESCALAR_128
}ADC_PRESCALAR;

typedef enum{
	AREF, 
	AVCC = 0x40,
	INTERNAL_2_56_REF = 0xC0
}ADC_REF;
typedef enum{
	ADCL_8bit = 0x00,
	ADCH_8bit = 0x20
}ADC_ADJUST;
typedef enum{
	Trigger_FreeRunning_Mode = 0x00,
	Trigger_AnalogComparator = 0x20,
	Trigger_EXT0 = 0x40,
	Trigger_Timer0_CMP = 0x60,
	Trigger_Timer0_OVF = 0x80,
	Trigger_Timer1_CMPB = 0xA0,
	Trigger_Timer1_OVF = 0xC0,
	Trigger_Timer1_ICU = 0xE0,
	Single_Conversion
}TriggerSource;

#define ADC_INT_ENABLE() SETBIT(ADCSRA, P3)
#define ADC_INT_DISABLE() CLEARBIT(ADCSRA, P3)

void ADC_init(ADC_PRESCALAR scaler, ADC_REF ref, ADCchannel channel, TriggerSource src);
uint32 ADC_StartConversion(ADC_ADJUST adj);
uint32 LM35_Conversion(uint32 vout);
float32 ADC_Vout(uint32 adc_out);
#endif /* ADC_H_ */