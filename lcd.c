/*
 * lcd.c
 *
 *  Created on: 17 Sep 2011
 *      Author: leraquendee
 */

#include <inttypes.h>
#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"

#define LCD_EN PORTA |= 0x04
#define LCD_DIS PORTA &= 0xFB

int LCD_busy ()
{
	DDRA = 0xFF;
	int pa = PORTA;
	PORTA |= 0x06;
	DDRA = 0x7F;

	int busy = (PINA & 0x80) >> 7;

	DDRA = 0xFF;
	PORTA = pa;

	return busy;
}

void LCD_command (int cmd)
{
	//while (LCD_busy() != 0);

	DDRA = 0xFF;
	PORTA = cmd & 0xF0;

	LCD_EN;
	LCD_DIS;

	PORTA = (cmd << 4) & 0xF0;

	LCD_EN;
	LCD_DIS;

	_delay_ms (2);
}

void LCD_init ()
{
	DDRA = 0xFF;
	PORTA = 0xFF;

	_delay_ms (16);

	LCD_command (0x28);

	_delay_ms (2);

	LCD_command (0x28);

	_delay_ms (2);

	LCD_command (0x0C);
	LCD_command (0x06);
	LCD_command (0x02);
	LCD_command (0x01);
	LCD_command (0x01);
}

void LCD_putc (char a)
{
	DDRA = 0xFF;
	PORTA = (a & 0xF0) | 0x01;

	LCD_EN;
	LCD_DIS;

	PORTA = ((a << 4) & 0xF0) | 0x01;

	LCD_EN;
	LCD_DIS;

	_delay_ms (2);
}

void LCD_print (char pos, char *str)
{
	int i=0;

	LCD_command (pos);

	for (i=0; str[i] != 0x00; i++)
	{
		LCD_putc (str[i]);
	}
}

void LCD_clear ()
{
	LCD_command (0x00);
}

void LCD_shift (int dir)
{
	switch(dir)
	{
	case LCD_DIR_RIGHT:
		LCD_command (0x1C);
		break;
	case LCD_DIR_LEFT:
		LCD_command (0x18);
		break;
	}
}
