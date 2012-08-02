/*
 * lcd.h
 *
 *  Created on: 17 Sep 2011
 *      Author: leraquendee
 */

#ifndef LCD_H_
#define LCD_H_


#endif /* LCD_H_ */

#define LCD_DIR_RIGHT 0
#define LCD_DIR_LEFT 1
#define LCD_FIRSTLINE_ADDR 0x80
#define LCD_SECONDLINE_ADDR 0xC0

int LCD_busy ();
void LCD_command (int cmd);
void LCD_init ();
void LCD_putc (char a);
void LCD_print (char pos, char *str);
void LCD_clear ();
void LCD_shift (int dir);
