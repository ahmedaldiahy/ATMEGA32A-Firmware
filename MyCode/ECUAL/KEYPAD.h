/*
 * KEYPAD.h
 *
 * Created: 1/7/2022 4:11:14 PM
 *  Author: ahmed
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "Config.h"

#define keyPad_DIR GPIOD->DDR.data
#define KeyPad_OUT GPIOD->PORT.data
#define keyPad_IN GPIOD->PIN.data

void keyPad_init();
uint8 checkButton();
uint8 getKeyPad_value();
void SEVEN_SEGMENT_init();
void SEVEN_DATA();
#endif /* KEYPAD_H_ */