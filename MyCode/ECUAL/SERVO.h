/*
 * SERVO.h
 *
 * Created: 12/20/2021 3:54:50 PM
 *  Author: ahmed
 */ 


#ifndef SERVO_H_
#define SERVO_H_

#include "Config.h"

#define servo_DIR GPIOD->DDR.data
#define servo_OUT GPIOD->PORT.data
#define servo_IN GPIOD->PIN.data
#define servo_PIN 4

void SERVO_START(uint16 freq, uint16 duty);


#endif /* SERVO_H_ */