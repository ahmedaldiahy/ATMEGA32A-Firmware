/*
 * LCD.h
 *
 * Created: 12/16/2021 10:26:30 PM
 *  Author: ahmed
 */ 


#ifndef LCD_H_
#define LCD_H_

#include "Config.h"
//Data 
#define DIR_data GPIOA->DDR.data
#define OUT_data GPIOA->PORT.data
#define IN_data GPIOA->PIN.data

//Control
#define DIR_control GPIOA->DDR.data
#define OUT_control GPIOA->PORT.data
#define IN_control GPIOA->PIN.data

#define RS P0
#define RW P1
#define E P2

#define eight_bitdata 0 // 1 for eight-bitdata, 0 for four-bitdata
#define upper_bits_four_bitdata 1 // 1 for upper , 0 for lower
#define _5x10_dot 0 // 1 for 5x10 , 0 for 5x8
#define two_lines 1 // 1 for 2 lines , 0 for one line
#define cursor 1 // 1 for enable cursor, 0 for disable
#define blinking_cursor 1 //1 for blinking cursor , 0 for disable it
#define display 1 //1 for display on , 0 for display off

#if (_5x10_dot && two_lines)
	#pragma  GCC error "you can't write 5x10 character in two lines"
#endif

#define CLEAR_DISPLAY 0x01
#define RETURN_HOME 0x02
#define DISPLAY ( (0x08)| (display<<2) | (cursor<<1) | (blinking_cursor) )
#define DATA_SET ( (0x20) | (eight_bitdata << 4) | (two_lines << 3) | (_5x10_dot << 2) )
#define DDRAM 0x80
#define CGRAM 0x40

typedef enum row{
	first_row = 0x00,
	second_row = 0x40
}row;
typedef enum col{
	col_0, col_1, col_2, col_3, col_4, col_5, col_6, col_7, col_8, col_9, col_10, col_11, col_12, col_13, col_14, col_15
}col;

void LCD_init();
void LCD_SEND_DATA(uint8 data);
void LCD_SEND_INSTRUCTION(uint8 address);
void LCD_SEND_STRING(uint8* str);
void LCD_SEND_INT(uint32 n);
void LCD_CLEAR();
void LCD_GOTO(row row, col col);
void LCD_DRAW_CHAR(uint8* data);

#endif /* LCD_H_ */