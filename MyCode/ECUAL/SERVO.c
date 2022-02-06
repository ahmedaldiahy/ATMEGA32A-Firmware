/*
 * SERVO.c
 *
 * Created: 12/20/2021 4:01:05 PM
 *  Author: ahmed
 */ 
#include "SERVO.h"

void SERVO_START(uint16 freq, uint16 duty){
	SETBIT(servo_DIR, servo_PIN);
	OCR1A(freq);
	OCR1B(duty);
	INIT_TIMER1(FAST_PWM_OCR1A, PRESCALAR_8, TIMER1_DISABLE_INT, OC1A_DISCONECT, FAST_PWM_OC1B_NON_INVERTING);

	/*//1000
	OCR1BH = 3;
	OCR1BL = 232;*/
	
	//2000
	/*OCR1BH = 7;
	OCR1BL = 208;
	*/
	
	/*
	//1500
	OCR1BH = 5;
	OCR1BL = 220;
	*/
}
