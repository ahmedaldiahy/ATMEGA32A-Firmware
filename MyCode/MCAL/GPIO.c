/*
 * GPIO.c
 *
 * Created: 11/17/2021 4:48:05 PM
 *  Author: ahmed
 */ 

#include "GPIO.h"
void DIR(GPIOreg* g, PinMode pm, PinNum pn){
	switch(pm){
		case OUTPUT:
			SETBIT(g->DDR.data, pn);
			break;
		case INPUTFLOAT:
			CLEARBIT(g->DDR.data, pn);
			CLEARBIT(g->PORT.data, pn);
			break;
		case INPUTPULLUP:
			CLEARBIT(g->DDR.data, pn);
			SETBIT(g->PORT.data, pn);
			break;
		default: break;
	}
}

void OUT(GPIOreg* g, PinNum pn, DigitalSignal d){
	switch(d){
		case LOW:
			CLEARBIT(g->PORT.data, pn);
			break;
		case HIGH:
			SETBIT(g->PORT.data, pn);
			break;
		default:break;
	}
}

DigitalSignal IN(GPIOreg* g,PinNum pn){
	return ISBITSET(g->PIN.data, pn);
}