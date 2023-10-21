/*
 * LCD.h
 *
 * Created: 10/20/2023 11:39:49 AM
 *  Author: Dewmith
 */ 


#ifndef LCD_H_
#define LCD_H_

void LCD_init();

//function to turn String into ASCII values
void LCD_print(char string[32]);

void LCD_set_cursor(short row, short coloumn);

void LCD_clear();



#endif /* LCD_H_ */