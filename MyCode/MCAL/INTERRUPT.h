/*
 * INTERRUPT.h
 *
 * Created: 11/17/2021 5:49:04 PM
 *  Author: ahmed
 */ 


#ifndef INTERRUPT_H_
#define INTERRUPT_H_
#include "Config.h"

#define SREG ((volatile uint8*)(0x5f))
#define GICR ((volatile uint8*)(0x5b))
#define GIFR ((volatile uint8*)(0x5a))
#define MCUCR ((volatile uint8*)(0x55))
#define MCUCSR ((volatile uint8*)(0x54))

#define INT0 __vector_1
#define INT1 __vector_2
#define INT2 __vector_3
#define BAD_INT __vector_default
#define ISR_NOBLOCK __attribute__((interrupt))
#define ISR_NAKED __attribute__((naked))


#define sei() __asm__ __volatile__ ("sei" ::)
#define cli() __asm__ __volatile__ ("cli" ::)
#define reti() __asm__ __volatile__ ("reti" ::)

#define ISR(name, ...) \
void name (void) __attribute__ ((signal)) __VA_ARGS__;\
void name(void)


//CallBack Interrupt
void (*INT0_ptr)(void);
void (*INT1_ptr)(void);
void (*INT2_ptr)(void);

typedef enum{
	INT0_EXT = 0x40,
	INT1_EXT = 0x80,
	INT2_EXT = 0x20
}INTNAME;
typedef enum{
	INT0_MODE_LOW = 0x00,
	INT0_MODE_ANY = 0x01,
	INT0_MODE_FALLING = 0x02,
	INT0_MODE_RISING = 0x03,
	
	INT1_MODE_LOW = 0x00,
	INT1_MODE_ANY = 0x04,
	INT1_MODE_FALLING = 0x08,
	INT1_MODE_RISING = 0x0C,
	
	INT2_MODE_FALLING = 0x00,
	INT2_MODE_RISING = 0x40,
}INTMODE;

#define GIE() SETBIT(*SREG, P7)
#define GID() CLEARBIT(*SREG, P7)

void ENABLEINT(INTNAME n, INTMODE m);
void DISABLEINT(INTNAME n);
void SETCALLBACKINT(INTNAME INT, void (*ptrINT) (void));

#endif /* INTERRUPT_H_ */