/*
 * I2C.c
 *
 * Created: 1/26/2022 1:45:59 AM
 *  Author: ahmed
 */ 
#include "I2C.h"

ISR(TWI_INT){
	I2C_status state = (TWSR&0xF8);
	switch(state){
		case I2C_START_CON:
			I2C_WRITE((0x40));
			SETBIT(GPIOA->PORT.data, P0);
			break;
		case I2C_TR_SLA_W_ACK:
			SETBIT(GPIOA->PORT.data, P1);
			I2C_WRITE('a');
			break;
		case I2C_TR_DATA_ACK:
			SETBIT(GPIOA->PORT.data, P2);
			//I2C_WRITE('b');
			I2C_STOP();
			break;
		default:break;
			
	}
}
void I2C_INIT(I2C_PRESCALER scaler, I2C_SPEED speed, I2C_INTERRUPT interrupt, uint8 address){
	
	/*
		FCL = F_CPU / 16+(2*TWBR)*4^n;
		TWBR = (F_CPU / (FCL *2 * 4^n))-(8/4^n)
	*/
	
	switch(scaler){
		case I2C_PRESCALER1:
			TWBR = (uint8)( ( ((float)F_CPU) / (speed*2.0) ) - 8 );
			break;
		case I2C_PRESCALER4:
			TWBR = (uint8)( ( ((float)F_CPU) / (speed*8.0) ) - 2 );
			break;
		case I2C_PRESCALER16:
			TWBR = (uint8)( ( ((float)F_CPU) / (speed*32.0) ) - .5 );
			break;
		case I2C_PRESCALER64:
			TWBR = (uint8)( ( ((float)F_CPU) / (speed*128.0) ) - .125 );
			break;
		default:break;
	}
	TWSR &= 0xFC;
	TWSR |= (scaler);
	TWAR = address<<1;
	TWCR &= (0x00);
	TWCR |= (1<<TWEN)|(interrupt);
}

void I2C_START(){
	static idx = 0;
	TWCR &= (0x07);
	TWCR |= (1<<TWINT);
	SETBIT(TWCR, TWSTA);
	while(ISBITCLEAR(TWCR, TWINT));
}
void I2C_STOP(){
	TWCR &= (0x07);
	TWCR |= (1<<TWINT);
	SETBIT(TWCR, TWSTO);
}
void I2C_WRITE(uint8 data){
	TWDR = data;
	TWCR &= (0x07);
	TWCR |= (1<<TWINT);
	while(ISBITCLEAR(TWCR, TWINT));
}
uint8 I2C_READ_ACK(){
	TWCR &= (0x07);
	TWCR |= (1<<TWINT);
	TWCR|=(1<<TWEA);
	while(ISBITCLEAR(TWCR, TWINT));
	return TWDR;
}
uint8 I2C_READ_NOACK(){
	TWCR &= (0x07);
	TWCR |= (1<<TWINT);
	while(ISBITCLEAR(TWCR, TWINT));
	return TWDR;
}
uint8 I2C_get_status(){
	return (TWSR&0xF8);
}


uint8 I2C_WRITE_BYTE(uint8 address, uint8 data){
	I2C_START();
	if ( I2C_get_status() != I2C_START_CON){
		I2C_STOP();
		return I2C_get_status();
	}
	I2C_WRITE(address<<1);
	if(I2C_get_status() != I2C_TR_SLA_W_ACK){
		I2C_STOP();
		return I2C_get_status();
	}
	I2C_WRITE(data);
	if(I2C_get_status() != I2C_TR_DATA_ACK){
		I2C_STOP();
		return I2C_get_status();
	}
	I2C_STOP();
	return 1;
}


/*void I2C_LCD_INIT(){
	//return home
	I2C_START();
	while( (TWSR & 0xf8) != I2C_START_CON);
	I2C_WRITE((0x70));
	while( (TWSR & 0xf8) != I2C_TR_SLA_W_ACK);
	I2C_WRITE(0x00);
	while( (TWSR & 0xf8) != I2C_TR_DATA_ACK);
	I2C_STOP();
	
	I2C_START();
	while( (TWSR & 0xf8) != I2C_START_CON);
	I2C_WRITE((0x70));
	while( (TWSR & 0xf8) != I2C_TR_SLA_W_ACK);
	I2C_WRITE(0x02);
	while((TWSR & 0xf8) != I2C_TR_DATA_ACK);
	I2C_STOP();
	
	I2C_START();
	while( (TWSR & 0xf8) != I2C_START_CON);
	I2C_WRITE((0x70));
	while( (TWSR & 0xf8) != I2C_TR_SLA_W_ACK);
	I2C_WRITE(0x02);
	while((TWSR & 0xf8) != I2C_TR_DATA_ACK);
	I2C_STOP();
	
	I2C_START();
	while( (TWSR & 0xf8) != I2C_START_CON);
	I2C_WRITE((0x70));
	while( (TWSR & 0xf8) != I2C_TR_SLA_W_ACK);
	I2C_WRITE(0x00);
	while((TWSR & 0xf8) != I2C_TR_DATA_ACK);
	I2C_STOP();
	
	I2C_START();
	while( (TWSR & 0xf8) != I2C_START_CON);
	I2C_WRITE((0x70));
	while( (TWSR & 0xf8) != I2C_TR_SLA_W_ACK);
	I2C_WRITE(0x02);
	while((TWSR & 0xf8) != I2C_TR_DATA_ACK);
	I2C_STOP();
	
	I2C_START();
	while( (TWSR & 0xf8) != I2C_START_CON);
	I2C_WRITE((0x70));
	while( (TWSR & 0xf8) != I2C_TR_SLA_W_ACK);
	I2C_WRITE(0x22);
	while((TWSR & 0xf8) != I2C_TR_DATA_ACK);
	I2C_STOP();
	
	I2C_START();
	while( (TWSR & 0xf8) != I2C_START_CON);
	I2C_WRITE((0x70));
	while( (TWSR & 0xf8) != I2C_TR_SLA_W_ACK);
	I2C_WRITE(0x00);
	while((TWSR & 0xf8) != I2C_TR_DATA_ACK);
	I2C_STOP();
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////	
	
	//Display
	
	I2C_START();
	while( (TWSR & 0xf8) != I2C_START_CON);
	I2C_WRITE((0x70));
	while( (TWSR & 0xf8) != I2C_TR_SLA_W_ACK);
	I2C_WRITE(0x00);
	while((TWSR & 0xf8) != I2C_TR_DATA_ACK);
	I2C_STOP();
	
	I2C_START();
	while( (TWSR & 0xf8) != I2C_START_CON);
	I2C_WRITE((0x70));
	while( (TWSR & 0xf8) != I2C_TR_SLA_W_ACK);
	I2C_WRITE(0x02);
	while((TWSR & 0xf8) != I2C_TR_DATA_ACK);
	I2C_STOP();
	
	I2C_START();
	while( (TWSR & 0xf8) != I2C_START_CON);
	I2C_WRITE((0x70));
	while( (TWSR & 0xf8) != I2C_TR_SLA_W_ACK);
	I2C_WRITE(0x02);
	while((TWSR & 0xf8) != I2C_TR_DATA_ACK);
	I2C_STOP();
	
	I2C_START();
	while( (TWSR & 0xf8) != I2C_START_CON);
	I2C_WRITE((0x70));
	while( (TWSR & 0xf8) != I2C_TR_SLA_W_ACK);
	I2C_WRITE(0x00);
	while((TWSR & 0xf8) != I2C_TR_DATA_ACK);
	I2C_STOP();
	
	I2C_START();
	while( (TWSR & 0xf8) != I2C_START_CON);
	I2C_WRITE((0x70));
	while( (TWSR & 0xf8) != I2C_TR_SLA_W_ACK);
	I2C_WRITE(0x02);
	while((TWSR & 0xf8) != I2C_TR_DATA_ACK);
	I2C_STOP();
	
	I2C_START();
	while( (TWSR & 0xf8) != I2C_START_CON);
	I2C_WRITE((0x70));
	while( (TWSR & 0xf8) != I2C_TR_SLA_W_ACK);
	I2C_WRITE(0xF2);
	while((TWSR & 0xf8) != I2C_TR_DATA_ACK);
	I2C_STOP();
	
	I2C_START();
	while( (TWSR & 0xf8) != I2C_START_CON);
	I2C_WRITE((0x70));
	while( (TWSR & 0xf8) != I2C_TR_SLA_W_ACK);
	I2C_WRITE(0x00);
	while((TWSR & 0xf8) != I2C_TR_DATA_ACK);
	I2C_STOP();
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	
	//DAtaset
	
	I2C_START();
	while( (TWSR & 0xf8) != I2C_START_CON);
	I2C_WRITE((0x70));
	while( (TWSR & 0xf8) != I2C_TR_SLA_W_ACK);
	I2C_WRITE(0x00);
	while((TWSR & 0xf8) != I2C_TR_DATA_ACK);
	I2C_STOP();
	
	I2C_START();
	while( (TWSR & 0xf8) != I2C_START_CON);
	I2C_WRITE((0x70));
	while( (TWSR & 0xf8) != I2C_TR_SLA_W_ACK);
	I2C_WRITE(0x02);
	while((TWSR & 0xf8) != I2C_TR_DATA_ACK);
	I2C_STOP();
	
	I2C_START();
	while( (TWSR & 0xf8) != I2C_START_CON);
	I2C_WRITE((0x70));
	while( (TWSR & 0xf8) != I2C_TR_SLA_W_ACK);
	I2C_WRITE(0x32);
	while((TWSR & 0xf8) != I2C_TR_DATA_ACK);
	I2C_STOP();
	
	I2C_START();
	while( (TWSR & 0xf8) != I2C_START_CON);
	I2C_WRITE((0x70));
	while( (TWSR & 0xf8) != I2C_TR_SLA_W_ACK);
	I2C_WRITE(0x00);
	while((TWSR & 0xf8) != I2C_TR_DATA_ACK);
	I2C_STOP();
	
	I2C_START();
	while( (TWSR & 0xf8) != I2C_START_CON);
	I2C_WRITE((0x70));
	while( (TWSR & 0xf8) != I2C_TR_SLA_W_ACK);
	I2C_WRITE(0x02);
	while((TWSR & 0xf8) != I2C_TR_DATA_ACK);
	I2C_STOP();
	_delay_ms(1);
	
	I2C_START();
	while( (TWSR & 0xf8) != I2C_START_CON);
	I2C_WRITE((0x70));
	while( (TWSR & 0xf8) != I2C_TR_SLA_W_ACK);
	I2C_WRITE(0xC2);
	while((TWSR & 0xf8) != I2C_TR_DATA_ACK);
	I2C_STOP();
	
	I2C_START();
	while( (TWSR & 0xf8) != I2C_START_CON);
	I2C_WRITE((0x70));
	while( (TWSR & 0xf8) != I2C_TR_SLA_W_ACK);
	I2C_WRITE(0x00);
	while((TWSR & 0xf8) != I2C_TR_DATA_ACK);
	I2C_STOP();
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	//ClearDisplay
	
	I2C_START();
	while( (TWSR & 0xf8) != I2C_START_CON);
	I2C_WRITE((0x70));
	while( (TWSR & 0xf8) != I2C_TR_SLA_W_ACK);
	I2C_WRITE(0x00);
	while((TWSR & 0xf8) != I2C_TR_DATA_ACK);
	I2C_STOP();
	
	I2C_START();
	while( (TWSR & 0xf8) != I2C_START_CON);
	I2C_WRITE((0x70));
	while( (TWSR & 0xf8) != I2C_TR_SLA_W_ACK);
	I2C_WRITE(0x02);
	while((TWSR & 0xf8) != I2C_TR_DATA_ACK);
	I2C_STOP();
	
	I2C_START();
	while( (TWSR & 0xf8) != I2C_START_CON);
	I2C_WRITE((0x70));
	while( (TWSR & 0xf8) != I2C_TR_SLA_W_ACK);
	I2C_WRITE(0x02);
	while((TWSR & 0xf8) != I2C_TR_DATA_ACK);
	I2C_STOP();
	
	I2C_START();
	while( (TWSR & 0xf8) != I2C_START_CON);
	I2C_WRITE((0x70));
	while( (TWSR & 0xf8) != I2C_TR_SLA_W_ACK);
	I2C_WRITE(0x00);
	while((TWSR & 0xf8) != I2C_TR_DATA_ACK);
	I2C_STOP();
	
	I2C_START();
	while( (TWSR & 0xf8) != I2C_START_CON);
	I2C_WRITE((0x70));
	while( (TWSR & 0xf8) != I2C_TR_SLA_W_ACK);
	I2C_WRITE(0x02);
	while((TWSR & 0xf8) != I2C_TR_DATA_ACK);
	I2C_STOP();
	
	I2C_START();
	while( (TWSR & 0xf8) != I2C_START_CON);
	I2C_WRITE((0x70));
	while( (TWSR & 0xf8) != I2C_TR_SLA_W_ACK);
	I2C_WRITE(0x12);
	while((TWSR & 0xf8) != I2C_TR_DATA_ACK);
	I2C_STOP();
	
	I2C_START();
	while( (TWSR & 0xf8) != I2C_START_CON);
	I2C_WRITE((0x70));
	while( (TWSR & 0xf8) != I2C_TR_SLA_W_ACK);
	I2C_WRITE(0x00);
	while((TWSR & 0xf8) != I2C_TR_DATA_ACK);
	I2C_STOP();
	
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	
	I2C_START();
	while( (TWSR & 0xf8) != I2C_START_CON);
	I2C_WRITE((0x70));
	while( (TWSR & 0xf8) != I2C_TR_SLA_W_ACK);
	I2C_WRITE(0x01);
	while((TWSR & 0xf8) != I2C_TR_DATA_ACK);
	I2C_STOP();
	
	I2C_START();
	while( (TWSR & 0xf8) != I2C_START_CON);
	I2C_WRITE((0x70));
	while( (TWSR & 0xf8) != I2C_TR_SLA_W_ACK);
	I2C_WRITE(0x03);
	while((TWSR & 0xf8) != I2C_TR_DATA_ACK);
	I2C_STOP();
	
	I2C_START();
	while( (TWSR & 0xf8) != I2C_START_CON);
	I2C_WRITE((0x70));
	while( (TWSR & 0xf8) != I2C_TR_SLA_W_ACK);
	I2C_WRITE(0x43);
	_delay_ms(1000);
	while((TWSR & 0xf8) != I2C_TR_DATA_ACK);
	I2C_STOP();
	
	I2C_START();
	while( (TWSR & 0xf8) != I2C_START_CON);
	I2C_WRITE((0x70));
	while( (TWSR & 0xf8) != I2C_TR_SLA_W_ACK);
	I2C_WRITE(0x41);
	while((TWSR & 0xf8) != I2C_TR_DATA_ACK);
	_delay_ms(1000);
	I2C_STOP();
	
	I2C_START();
	while( (TWSR & 0xf8) != I2C_START_CON);
	I2C_WRITE((0x70));
	while( (TWSR & 0xf8) != I2C_TR_SLA_W_ACK);
	I2C_WRITE(0x03);
	while((TWSR & 0xf8) != I2C_TR_DATA_ACK);
	I2C_STOP();
	
	I2C_START();
	while( (TWSR & 0xf8) != I2C_START_CON);
	I2C_WRITE((0x70));
	while( (TWSR & 0xf8) != I2C_TR_SLA_W_ACK);
	I2C_WRITE(0x13);
	while((TWSR & 0xf8) != I2C_TR_DATA_ACK);
	I2C_STOP();
	
	I2C_START();
	while( (TWSR & 0xf8) != I2C_START_CON);
	I2C_WRITE((0x70));
	while( (TWSR & 0xf8) != I2C_TR_SLA_W_ACK);
	I2C_WRITE(0x11);
	while((TWSR & 0xf8) != I2C_TR_DATA_ACK);
	I2C_STOP();
	SETBIT(GPIOA->PORT.data, P4);
}*/
/*
start i2c
send address
send data 
stop
*/

/*
start i2c
send address
start i2c rep
send address|1
get data 
stop
*/