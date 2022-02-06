/*
 * EEPROM.h
 *
 * Created: 1/29/2022 7:07:17 PM
 *  Author: ahmed
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_

#include "Config.h"

#define EECR (*(volatile uint8*)(0x3C))
//INTE, write enable, completion,read enable
#define EEARL (*(volatile uint8*)(0x3E))
#define EEARH (*(volatile uint8*)(0x3F))
#define EEDR (*(volatile uint8*)(0x3D))

#define EERIE P3
#define EEMWE P2
#define EEWE P1
#define EERE P0

#define EEAR(address) do{\
	EEARH = ( (address>>8) & (0x03) );\
	EEARL = (uint8)(address);\
}while(0);

void EEPORM_WRITE(uint8 address, uint8 data);
uint8 EEPROM_READ(uint8 address);

#endif /* EEPROM_H_ */