/*
 * SEVEN_SEG.c
 *
 * Created: 1/7/2022 7:20:18 PM
 *  Author: ahmed
 */ 

/*
A 0				A
B 1
C 2			F		B
D 3				G
E 4			E		C
F 5				D
G 6
DF 7
*/
#include "KEYPAD.h"

#define SEVEN_SEGMENT_DIR GPIOA->DDR.data
#define SEVEN_SEGMENT_OUT GPIOA->PORT.data
#define SEVEN_SEGMENT_IN GPIOA->PIN.data

typedef enum{
	zero = 63,
	one = 48,
	two = 91,
	three = 79,
	four = 102,
	five = 109,
	six = 125,
	seven = 7,
	eight = 127,
	nine = 111
}seven_nums;

seven_nums seven_display[10] = {zero, one, two, three, four, five, six, seven, eight, nine};
	
void SEVEN_SEGMENT_init(){
	SEVEN_SEGMENT_DIR = 0b11111111;
}
void SEVEN_DATA(){
	static uint8 idx = 0;
	SEVEN_SEGMENT_OUT = seven_display[idx++];
	if(idx == 10) idx = 0;
}


