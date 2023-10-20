/**
 * @file TWI.c
 * @author Dewmith Ranasinghe (dewmithrana@gmail.com)
 * @brief 
 * @version 0.1
 * @date 01-08-2023
 *  
 */
#include <avr/io.h>
#include <stdbool.h>
#include "TWI.h"

#define F_CPU 16000000UL

bool check_status()
{
  //uint8_t tmp = TWSR & 0xF8;
  //switch(tmp){
    //case 0x08: //a start condition has been transmitted
		//return true;
		//break;
    //case 0x18: //SLA_W + ACK
		//return true;
		//break;
    //case 0x20: //SLA_W + NACK
		//return false;
		//break;
    //case 0x28: //data + ACK
		//return true;
		//break;
    //case 0x30: //data + NACK
		//return false;
		//break;
    //case 0x38: //lost
		//return false;
		//break;
    //default:
		//return false;
		//break;
  //}
	return true;   
}

static void TWI_WAIT()
{
  while (!(TWCR & (1<<TWINT)));
}

void TWI_STOP()
{
  TWI_WAIT();
  TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
}

void TWI_START()
{
  TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
  TWI_WAIT();
  if(!(check_status())){
      TWI_STOP();
  }
}

void TWI_REPEATED_START()
{
  TWI_WAIT();
  TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);  
  if(!(check_status())){
      TWI_STOP();
  }  
}

void TWI_DATA_WRITE(uint8_t data )
{
  TWI_WAIT();
  TWDR = data; 
  TWCR = (1<<TWINT)|(1<<TWEN); 
  if(!(check_status())){
      TWI_STOP();
  }  
}


void TWI_ADDRESS_WRITE(uint8_t address , char mode )
{
  
  TWI_WAIT();  
  if(READ == mode)
  {      
      TWDR = address<<1 | 1; 
  }
  else if(WRITE == mode)
  {  
      TWDR = address<<1 | 0; 
  }
  else
  {
	  //no implementation
  }
  
  TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
  if(!(check_status())){
      TWI_STOP();
  }
}

void TWI_READ(uint8_t numofbytes , uint8_t * data)
{
	
	for(uint8_t index = 0; index < numofbytes; index++)
	{
		TWI_WAIT();
		data[index] = TWDR;
		if(index != numofbytes-1){
			TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
		}
		else{
			TWCR = (1<<TWINT)|(1<<TWEN);
		}
	}
}

void TWI_init()
{   
  
  TWBR = (((F_CPU/BIT_RATE) - 16)/2) & (0xff);
  TWSR &= ~0x03; 
  TWCR = (1<<TWEA)|(1<<TWEN)|(1<<TWIE);   
}
