/*
 * WatchDog.c
 *
 * Created: 1/8/2022 9:40:44 PM
 *  Author: ahmed
 */ 
#include "WatchDog.h"

void WDT_ENABLE(WDT_PreScaler scaler){
	WDTCR &= 0xF8;
	WDTCR|=scaler;
	SETBIT(WDTCR, WDE);
}
void WDT_DISABLE(){
	SETBIT(WDTCR, WDTOE);
	SETBIT(WDTCR, WDE);
	_delay_us(4);
	CLEARBIT(WDTCR, WDE);
}
