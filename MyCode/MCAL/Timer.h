/*
 * Timer.h
 *
 * Created: 11/27/2021 6:09:29 PM
 *  Author: ahmed
 */ 


#ifndef TIMER_H_
#define TIMER_H_
#include "Config.h"

//INTERRUPT
#define TIMSK (*(volatile uint8*)(0x59))
#define TIFR (*(volatile uint8*)(0x58))
//TIMER0_REG
#define TCCR0 (*(volatile uint8*)(0x53)) 
#define TCNT0 (*(volatile uint8*)(0x52))
#define OCR0 (*(volatile uint8*)(0x5C))
//TIMER1_REG
#define TCCR1A (*(volatile uint8*)(0x4F))
#define TCCR1B (*(volatile uint8*)(0x4E))
#define TCNT1H (*(volatile uint8*)(0x4D))
#define TCNT1L (*(volatile uint8*)(0x4C))
#define OCR1AH (*(volatile uint8*)(0x4B))
#define OCR1AL (*(volatile uint8*)(0x4A))
#define OCR1BH (*(volatile uint8*)(0x49))
#define OCR1BL (*(volatile uint8*)(0x48))
#define ICR1H (*(volatile uint8*)(0x47))
#define ICR1L (*(volatile uint8*)(0x46)) 



#define Timer2_OCF __vector_4
#define Timer2_OVF __vector_5
#define Timer1_ICF __vector_6
#define Timer1_OCFA __vector_7
#define Timer1_OCFB __vector_8
#define Timer1_OVF __vector_9
#define Timer0_OCF __vector_10
#define Timer0_OVF __vector_11

#define TCNT1(n) do{\
	TCNT1H = (n>>8);\
	TCNT1L = n;\
	}while(0);
#define OCR1A(n) do{\
	OCR1AH = (n>>8);\
	OCR1AL = n;\
	}while(0);

#define OCR1B(n) do{\
	OCR1BH = (n>>8);\
	OCR1BL = n;\
}while(0);

#define ICU1 (ICR1L)|(ICR1H<<8)
/*
TCCR0

FOC0|WGM00|COM01|COM00|WGM01|CS02|CS01|CS00
0x00
0x10
0x20
0x30


*/
#define FORCE_OCR0() SETBIT(TCCR0, P7)

typedef enum{
	NO_CLOCK_STOP_TIMER = 0X00,
	NO_PRESCALAR,
	PRESCALAR_8,
	PRESCALAR_64,
	PRESCALAR_256,
	PRESCALAR_1024,
	EXT_CLOCK_ON_FALLING_EDGE,
	EXT_CLOCK_ON_RISING_EDGE
}CLOCKTIMERSEL;

typedef enum{
	OVF_MODE = 0x00,
	CTC_MODE = 0x08,
	PWM_PHASE_CORRECT = 0x40,
	PWM_FAST = 0x48
}TIMER0MODE;
typedef enum{
	TiMER0_DISABLE_INT = 0x00,
	TiMER0_OVF_INT,
	TiMER0_CMP_INT,
	TiMER0_OVF_CMP_INT
}INTTIMER0SEL;

typedef enum{
	OC0_DISCONECT = 0x00,
	
	OC0_NONPWM_TOGGLE = 0x10,
	OC0_NON_PWM_CLEAR = 0x20,
	OC0_NONPWM_SET = 0x30,
	
	OC0_PWMFAST_NONINVERT = 0x20,
	OC0_PWMFAST_INVERT = 0x30,
	
	OC0_PWMPHCH_INVERT = 0x20,
	OC0_PWMPHCH_NONINVERT = 0x30

	
}OC0_ACTION;


typedef enum{
	OVF_TIMER1_MODE = 0x00,
	CTC_MODE_OCR1A = 0x10,
	CTC_MODE_ICR1 = 0x30,
	FAST_PWM_ICR1 = 0x32,
	FAST_PWM_OCR1A = 0x33
}TIMER1MODE;

typedef enum{
	OC1A_DISCONECT = 0x00,
	NONPWM_OC1A_TOGGLE = 0x40,
	NONPWM_OC1A_CLEAR = 0x80,
	NONPWM_OC1A_SET = 0xc0,
	
	FAST_PWM_OC1A_NON_INVERTING = 0x80,
	FAST_PWM_OC1A_INVERTING = 0xc0,
	
	PH_PWM_OC1A_INVERTING = 0xc0,
	PH_PWM_OC1A_NON_INVERTING = 0x80
	
}OC1A_ACTION;

typedef enum{
	OC1B_DISCONECT = 0x00,
	NONPWM_OC1B_TOGGLE = 0x10,
	NONPWM_OC1B_CLEAR = 020,
	NONPWM_OC1B_SET = 0x30,
	
	FAST_PWM_OC1B_NON_INVERTING = 0x20,
	FAST_PWM_OC1B_INVERTING = 0x30,
	
	PH_PWM_OC1B_INVERTING = 0x30,
	PH_PWM_OC1B_NON_INVERTING = 0x20
	
}OC1B_ACTION;

typedef enum{
	TIMER1_DISABLE_INT = 0x00,
	TIMER1_OVF_INT = 0x04,
	TIMER1_CMPB_INT = 0x08,
	TIMER1_CMPA_INT = 0x10,
	TIMER1_ICU_INT = 0x20,
	TIMER1_OVF_ICU_INT = 0x24,
	TIMER1_CMPA_CMPB_INT = 0x18,
	TIMER1_OVF_CMPA_CMPB_INT = 0x1c,
	TIMER1_CMPA_CMPB_ICU_INT = 0x38,
	TIMER1_OVF_CMPA_CMPB_ICU_INT = 0x3c,
}INTTIMER1SEL;

typedef enum{
	ICP_RISING = 0x40,
	ICP_FALLING = 0x00
}INPUTCAPTURE_MODE; 

void INIT_TIMER0(TIMER0MODE mode, CLOCKTIMERSEL clk, INTTIMER0SEL in, OC0_ACTION oc0);
void INIT_TIMER1(TIMER1MODE mode, CLOCKTIMERSEL clk, INTTIMER1SEL in, OC1A_ACTION oc1a, OC1B_ACTION oc1b);
void INPUT_CAPTURE_CONFIG(INPUTCAPTURE_MODE mode);
void ENABLE_TIMER1_INT(INTTIMER1SEL in);
void DISABLE_TIMER1_INT(INTTIMER1SEL in);
void STOP_TIMER1(void);
void STOP_TIMER0(void);
void ENABLE_TIMER1(CLOCKTIMERSEL clk);
void ENABLE_TIMER0(CLOCKTIMERSEL clk);

#endif /* TIMER_H_ */
