/*
 * STDTYPES.h
 *
 * Created: 11/17/2021 3:21:38 PM
 *  Author: ahmed
 */ 


#ifndef STDTYPES_H_
#define STDTYPES_H_

typedef unsigned char uint8;
typedef signed char sint8;

typedef unsigned short uint16;
typedef signed short sint16;

typedef unsigned long uint32;
typedef signed long sint32;

typedef unsigned long long uint64;
typedef signed long long sint64;

typedef float float32;
typedef double float64;
typedef long double float96;
typedef void* vptr;

#define myNULL (void*)(0)

typedef enum{LOW, HIGH}DigitalSignal;
typedef enum{P0, P1, P2, P3, P4, P5, P6, P7}PinNum;
typedef enum{OUTPUT, INPUTFLOAT, INPUTPULLUP}PinMode;
	
typedef union{
	volatile uint8 data;
	struct{
		volatile uint8 B0:1;
		volatile uint8 B1:1;
		volatile uint8 B2:1;
		volatile uint8 B3:1;
		volatile uint8 B4:1;
		volatile uint8 B5:1;
		volatile uint8 B6:1;
		volatile uint8 B7:1;
	}bits;

}reg8;

typedef struct{
	reg8 PIN;
	reg8 DDR;
	reg8 PORT;
}GPIOreg;

#define GPIOA ((GPIOreg*)(0x39))
#define GPIOB ((GPIOreg*)(0x36))
#define GPIOC ((GPIOreg*)(0x33))
#define GPIOD ((GPIOreg*)(0x30))
#endif /* STDTYPES_H_ */