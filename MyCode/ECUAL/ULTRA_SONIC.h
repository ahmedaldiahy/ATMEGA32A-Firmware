/*
 * ULTRA_SONIC.h
 *
 * Created: 12/20/2021 4:34:58 PM
 *  Author: ahmed
 */ 


#ifndef ULTRA_SONIC_H_
#define ULTRA_SONIC_H_

#include "Config.h"

#define Trig_ultra_DIR GPIOD->DDR.data
#define Trig_ultra_OUT GPIOD->PORT.data
#define Trig_ultra_IN GPIOD->PIN.data
#define Trig_ultra_PIN 7

uint32 START_ULTRA(void);

#endif /* ULTRA_SONIC_H_ */
