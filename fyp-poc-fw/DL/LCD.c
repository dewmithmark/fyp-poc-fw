/*
 * LCD.h
 *
 * Created: 10/20/2023 11:39:01 AM
 *  Author: Dewmith
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>

#include "TWI.h"
#include "LCD.h"

#define RS				0x01
#define RW				0x02
#define E				0x04

#define LCD_SA			0x27

#define BACKLIGHT_BM	0x80

uint8_t local_buffer;
char tmp; 
char buffer[32];
bool set_cursor_flag = false;


static void transmit_data(uint8_t data){
  TWI_START();
  TWI_ADDRESS_WRITE(LCD_SA , WRITE); 
  data |= E; //Generate High-to-Low pulse  
  TWI_DATA_WRITE(data | BACKLIGHT_BM); 
  
  _delay_ms(10);
  
  data &= ~E;
  TWI_DATA_WRITE(data | BACKLIGHT_BM); 
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
void LCD_print(char string[32])
{
    short i;
    for(i=0; string[i]!='\0'; i++){    
        tmp = string[i];
        LCD_write((int)tmp , 2);
    }
    if(set_cursor_flag != true){
        LCD_write(0XC0 , 1);
    }
   

}
void LCD_set_cursor(short row, short coloumn)
{
    set_cursor_flag = true;
    //int DDRAM[2][16]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,
                 //64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79};
    //int cursor_pos = DDRAM[row-1][coloumn-1] + 128;
    //LCD_write(cursor_pos , 1);
}
void LCD_clear()
{ 
   LCD_write(0x01 , 1);
}



