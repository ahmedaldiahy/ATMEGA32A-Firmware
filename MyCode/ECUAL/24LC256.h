/*
 * _24LC256.h
 *
 * Created: 1/31/2022 4:22:31 PM
 *  Author: ahmed
 */ 


#ifndef _24LC256_H_
#define _24LC256_H_


#include "Config.h"

#define _24LC256_address_WRITE 0b10100000
#define _24LC256_address_READ 0b10100001
//65536

void external_EEPROM_WRITE(uint16 address, uint8 data);
uint8 external_EEPROM_READ(uint16 address);


#endif /* 24LC256_H_ */
