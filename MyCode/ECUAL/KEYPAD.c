/*
 * KEYPAD.c
 *
 * Created: 1/7/2022 4:11:01 PM
 *  Author: ahmed
 */ 
#include "KEYPAD.h"

uint8 keyPad_value[4][4] = {{'7', '8', '9', '/'}, {'4', '5', '6', '*'}, {'1', '2', '3', '-'}, {'@', '0', '=', '+'} };

void keyPad_init(){
	keyPad_DIR = 0b00001111;
	KeyPad_OUT = 0b11111111;
}

uint8 getKeyPad_value(){
		
		uint8 key_val = -1;
		while(1){
			CLEARBIT(KeyPad_OUT, P0);
			key_val = checkButton();
			SETBIT(KeyPad_OUT, P0);
			if(key_val != 4)  return keyPad_value[key_val][0];
		
			CLEARBIT(KeyPad_OUT, P1);
			key_val = checkButton();
			SETBIT(KeyPad_OUT, P1);
			if(key_val != 4) return keyPad_value[key_val][1];
		
			CLEARBIT(KeyPad_OUT, P2);
			key_val = checkButton();
			SETBIT(KeyPad_OUT, P2);
			if(key_val != 4) return keyPad_value[key_val][2];
		
			CLEARBIT(KeyPad_OUT, P3);
			key_val = checkButton();
			SETBIT(KeyPad_OUT, P3);
			if(key_val != 4) return keyPad_value[key_val][3];
		}
	
}

uint8 checkButton(){
	
	if(ISBITCLEAR(keyPad_IN, P4)) return 0;
	if(ISBITCLEAR(keyPad_IN, P5)) return 1;
	if(ISBITCLEAR(keyPad_IN, P6)) return 2;
	if(ISBITCLEAR(keyPad_IN, P7)) return 3;
	
	return 4;
}

