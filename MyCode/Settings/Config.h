/*
 * Config.h
 *
 * Created: 11/17/2021 3:17:49 PM
 *  Author: ahmed
 */ 


#ifndef CONFIG_H_
#define CONFIG_H_

#define F_CPU (unsigned long)(8000000)
#include <util/delay.h>

#include "MACROS.h"
#include "STDTYPES.h"
#include "DELAY.h"
#include "GPIO.h"
#include "interrupt.h"
#include "Timer.h"
#include "SPI.h"
#include "LCD.h"
#include "SERVO.h"
#include "ULTRA_SONIC.h"
#include "ADC.h"
#include "UART.h"
#include "KEYPAD.h"
#include "WatchDog.h"
#include "UART_CONFIG.h"
#include "WIFI_MODULE.h"
#include "I2C.h"
#include "LCD_I2C.h"
#include "DS1307.h"
#include "EEPROM.h"
#include "24LC256.h"
#endif /* CONFIG_H_ */