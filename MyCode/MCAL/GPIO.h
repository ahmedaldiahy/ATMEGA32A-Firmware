/*
 * GPIO.h
 *
 * Created: 11/17/2021 4:43:31 PM
 *  Author: ahmed
 */ 


#ifndef GPIO_H_
#define GPIO_H_

#include "Config.h"

void DIR(GPIOreg* g, PinMode pm, PinNum pn);
void OUT(GPIOreg* g, PinNum pn, DigitalSignal d);
DigitalSignal IN(GPIOreg* g,PinNum pn);



#endif /* GPIO_H_ */