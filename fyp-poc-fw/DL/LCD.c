/*
 * LCD.h
 *
 * Created: 10/20/2023 11:39:01 AM
 *  Author: Dewmith
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "TWI.h"
#include "LCD.h"
#include "debug_utilis.h"

#define RS				0x01
#define RW				0x02
#define E				0x04

#define LCD_SA			0x27

#define BACKLIGHT_BM	0x08

char LCD_BUFFER[32];

uint8_t local_buffer;
char tmp; 
char buffer[32];

static void transmit_data(uint8_t data){
  TWI_START();
  TWI_ADDRESS_WRITE(LCD_SA , WRITE); 
  data |= E; //Generate High-to-Low pulse  
  TWI_DATA_WRITE(data | 0x08); 
  
  _delay_ms(10);
  
  data &= ~E;
  TWI_DATA_WRITE(data | 0x08); 
  TWI_STOP();
}

static void LCD_write(char data , short n)
{
  local_buffer = 0;
  if(n==1){
    local_buffer &= ~RS;//Set RS pin to LOW    
  }
  else if(n==2){
    local_buffer |= RS;//Set RS pin to High    
  }
  local_buffer &= ~RW;//Set RW pin to LOW
  local_buffer &= ~0xF0;  //clear the data bits
  local_buffer |= (data & 0xF0);    //Set upper 4 bits of the data 
  transmit_data(local_buffer);
  
  
   _delay_ms(10); 
    
  local_buffer &= ~0xF0;
  local_buffer |= ((data<<4) & 0xF0);    //Set lower 4 bits of the data 
  transmit_data(local_buffer);
  
}

void LCD_init()
{  
	 LCD_write(0x33 , 1); 
	 LCD_write(0x32 , 1); 
	 LCD_write(0x28 , 1); 
	 LCD_write(0x0C , 1);      
	 LCD_write(0x06 , 1);
	 LCD_write(0x01 , 1);
}

//function to turn String into ASCII values
void LCD_print(char *string)
{
    
    for(int i=0; string[i]!='\0'; i++)
	{    
        tmp = string[i];
        LCD_write((int)tmp , 2);
		_delay_ms(10); 
    }  

}

void LCD_set_cursor(short row, short coloumn)
{  
    static int cursor_pos = 0;	
	switch(row-1)
	{
		case 0:
		cursor_pos = (coloumn - 1) + 128;
		break;
		
		case 1:
		cursor_pos = (64 + (coloumn - 1)) + 128;
		break;
		
		case 2:
		cursor_pos = (16 + (coloumn - 1)) + 128;
		break;
		
		case 3:
		cursor_pos = (80 + (coloumn - 1)) + 128;
		break;
		
		default:
		break;
	}	
	LCD_write(cursor_pos , 1);	
}

void LCD_clear()
{ 
   LCD_write(0x01 , 1);
}


void LCD_print_float(double val)
{
	int int_part = (int)val;
	int dec_part = (int)((val - int_part) * 1000); // Extract 3 decimal places
	sprintf(LCD_BUFFER, "%d.%03d", int_part, dec_part);
	LCD_print(LCD_BUFFER);
}

