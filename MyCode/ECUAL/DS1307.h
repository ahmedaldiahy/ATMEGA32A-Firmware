/*
 * DS1307.h
 *
 * Created: 1/29/2022 2:18:26 PM
 *  Author: ahmed
 */ 


#ifndef DS1307_H_
#define DS1307_H_

#include "Config.h"

#define RTCS_WRITE_ADDRESS (0xD0)
#define RTCS_READ_ADDRESS (0xD1)
#define RTCS_COFIG_REG (0x07)
#define RTCS_SECONDS_REG (0x00)
#define RTCS_HOURS_REG (0x02)

typedef struct{
	uint8 sec;
	uint8 min;
	uint8 hour;
	uint8 wday;
	uint8 day;
	uint8 month;
	uint8 year;
}RTCS_DATE;
void RTCS_INIT();
void RTCS_SET_DATE(RTCS_DATE* set);
void RTCS_READ_DATE(RTCS_DATE* get);
void RTCS_PRINT_TIME(RTCS_DATE* rtc);
void RTCS_PRINT_DATE(RTCS_DATE* rtc);


#endif /* DS1307_H_ */