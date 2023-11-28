/*
 * LCD.h
 *
 * Created: 10/20/2023 11:39:49 AM
 *  Author: Dewmith
 */ 


#ifndef LCD_H_
#define LCD_H_

void LCD_init();
void LCD_print(char *string);
void LCD_set_cursor(short row, short coloumn);
void LCD_print_float(double val);
void LCD_clear();

#endif /* LCD_H_ */