/*
 * WatchDog.h
 *
 * Created: 1/8/2022 9:41:16 PM
 *  Author: ahmed
 */ 


#ifndef WATCHDOG_H_
#define WATCHDOG_H_

#include "Config.h"

#define WDTCR (*(volatile uint8*)(0x41))
// , WDE, prescaler2:0
#define WDE P3
#define WDTOE P4

typedef enum{
	
	//prescaler with timeout
	
	WDT_SCALER_16K, //16.3 ms
	WDT_SCALER_32K, //32.5 ms
	WDT_SCALER_64K, //65 ms
	WDT_SCALER_128K, //.13 s
	WDT_SCALER_256K, //.26 s
	WDT_SCALER_512K, //.52 s
	WDT_SCALER_1024K, //1 s
	WDT_SCALER_2048K //2.1 s
	
}WDT_PreScaler;

void WDT_ENABLE(WDT_PreScaler scaler);
void WDT_DISABLE();

#endif /* WATCHDOG_H_ */