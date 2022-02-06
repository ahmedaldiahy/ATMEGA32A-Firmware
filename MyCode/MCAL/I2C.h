/*
 * I2C.h
 *
 * Created: 1/26/2022 1:46:14 AM
 *  Author: ahmed
 */ 


#ifndef I2C_H_
#define I2C_H_

#include "Config.h"

#define TWCR (*(volatile uint8*)(0x56))
//twi flag, ack, start, stop, coll flag, twi enable, int enable
#define TWAR (*(volatile uint8*)(0x22))
#define TWDR (*(volatile uint8*)(0x23))
#define TWSR (*(volatile uint8*)(0x21))
#define TWBR (*(volatile uint8*)(0x20))

#define TWINT (P7)
#define TWIE (P0)
#define TWEN (P2)
#define TWSTO (P4)
#define TWSTA (P5)
#define TWEA (P6)

#define TWI_INT __vector_19

typedef enum{
	I2C_PRESCALER1,
	I2C_PRESCALER4,
	I2C_PRESCALER16,
	I2C_PRESCALER64
}I2C_PRESCALER;

typedef enum{
	I2C_100Kbps = 100000,
	I2C_400Kbps = 400000,
	I2C_3_3Mbps = 3300000
}I2C_SPEED;
typedef enum{
	I2C_DISABLEINT,
	I2C_ENABLEINT
}I2C_INTERRUPT;

typedef enum{
	I2C_START_CON = 0x08,
	I2C_REP_START_CON = 0x10,
	I2C_TR_SLA_W_ACK = 0x18,
	I2C_TR_SLA_W_NOACK = 0x20,
	I2C_TR_SLA_R_ACK = 0x40,
	I2C_TR_SLA_R_NOACK = 0x48,
	I2C_TR_DATA_ACK = 0x28,
	I2C_TR_DATA_NOACK = 0x30,
	I2C_REC_DATA_ACK = 0x50,
	I2C_REC_DATA_NOACK = 0x58,
	I2C_TR_SLA_ARB_LOST = 0x38,
}I2C_status;

void I2C_INIT(I2C_PRESCALER scaler, I2C_SPEED speed, I2C_INTERRUPT interrupt, uint8 address);
void I2C_START();
void I2C_STOP();
void I2C_WRITE(uint8 data);
uint8 I2C_READ_ACK();
uint8 I2C_READ_NOACK();
uint8 I2C_get_status();
uint8 I2C_WRITE_BYTE(uint8 address, uint8 data);

#endif /* I2C_H_ */