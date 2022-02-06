/*
 * EEPROM.c
 *
 * Created: 1/29/2022 7:07:04 PM
 *  Author: ahmed
 */ 
#include "EEPROM.h"
void EEPORM_WRITE(uint8 address, uint8 data){
	while(ISBITSET(EECR, EEWE));
	EEAR(address);
	EEDR = data;
	SETBIT(EECR, EEMWE);
	SETBIT(EECR, EEWE);
}
uint8 EEPROM_READ(uint8 address){
	while(ISBITSET(EECR, EEWE));
	EEAR(address);
	SETBIT(EECR, EERE);
	return EEDR;
}