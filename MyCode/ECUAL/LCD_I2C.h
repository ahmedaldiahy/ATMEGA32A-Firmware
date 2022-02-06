/*
 * I2C_APP.h
 *
 * Created: 1/28/2022 6:42:45 PM
 *  Author: ahmed
 */ 


#ifndef I2C_APP_H_
#define I2C_APP_H_

#include "Config.h"

void I2C_LCD_INIT(uint8);
void I2C_LCD_READ();
void I2C_LCD_SEND_DATA(uint8, uint8);
void I2C_LCD_SEND_INSTRUCTION(uint8, uint8);
void I2C_LCD_SEND_STRING(uint8*, uint8);


#endif /* I2C_APP_H_ */