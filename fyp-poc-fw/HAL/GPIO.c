/*
 * GPIO.c
 *
 * Created: 8/11/2023 9:48:37 AM
 *  Author: Dewmith
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include "GPIO.h"

void GPIO_SET_PIN(uint8_t pin, uint8_t port, uint8_t status)
{
	switch(port)
	{
		case _PORTB:
			if(INPUT == status)
			{
				DDRB &= ~(1 << pin); 
			}
			else if(OUTPUT == status)
			{
				DDRB |= (1 << pin); 
			}
			else if(INPUT_PULLUP == status)
			{
				DDRB &= ~(1 << pin); 
				PORTB |= (1 << pin); 	
			}
			break;
			
		case _PORTC:
			if(INPUT == status)
			{
				DDRC &= ~(1 << pin);
			}
			else if(OUTPUT == status)
			{
				DDRC |= (1 << pin);
			}
			else if(INPUT_PULLUP == status)
			{
				DDRC &= ~(1 << pin);
				PORTC |= (1 << pin);
			}
			break;
			
		case _PORTD:
			if(INPUT == status)
			{
				DDRD &= ~(1 << pin);
			}
			else if(OUTPUT == status)
			{
				DDRD |= (1 << pin);
			}
			else if(INPUT_PULLUP == status)
			{	
				DDRD &= ~(1 << pin);
				PORTD |= (1 << pin);
			}
			break;
			
		default:
			break;
	}
}

void GPIO_WRITE_PIN(uint8_t pin, uint8_t port, uint8_t status)
{
	switch(port)
	{
		case _PORTB:
			if(SET == status)
			{
				PORTB |= (1 << pin);
			}
			else if(RESET == status)
			{
				PORTB &= ~(1 << pin);
			}
			else
			{
				//no implementation
			}					
			break;
		
		case _PORTC:
			if(SET == status)
			{
				PORTC |= (1 << pin);
			}
			else if(RESET == status)
			{
				PORTC &= ~(1 << pin);
			}
			else
			{
				//no implementation
			}
			break;
		
		case _PORTD:
			if(SET == status)
			{
				PORTD |= (1 << pin);
			}
			else if(RESET == status)
			{
				PORTD &= ~(1 << pin);
			}
			else
			{
				//no implementation
			}
			break;
					
		default:
		break;
	}
}

uint8_t GPIO_READ_PIN(uint8_t pin, uint8_t port)
{
	switch(port)
	{
		case _PORTB:
			if (PINB & (1 << pin)) 
			{
				return 1;
			}
			else
			{
				return 0;
			}
			break;
			
		case _PORTC:
			if (PINC & (1 << pin))
			{
				return 1;
			}
			else
			{
				return 0;
			}
			break;
			
		case _PORTD:
			if (PIND & (1 << pin))
			{
				return 1;
			}
			else
			{
				return 0;
			}
			break;
			
		default:
			return 0;
		break;
	}
}

void GPIO_PCINT_SET(uint8_t pin, uint8_t port)
{
	PCMSK2 |= (1 << pin);  // Enable the Pin Change Interrupt for PD2 (PCINT18)
	switch(port)
	{
		case _PORTB:			
			PCICR |= (1 << PCIE0); // Enable Pin Change Interrupt 1
		    break;	
		
		case _PORTC:
			PCICR |= (1 << PCIE1);
			break;
		
		case _PORTD:
			PCICR |= (1 << PCIE2);
			break;
		
		default:
		break;
	}
	sei();
}

void GPIO_EXTINT_SET(uint8_t int_type, uint8_t trigger_edge)
{
	switch(trigger_edge)
	{
		case LOW:
			if(INT0 == int_type)
			{				
				EICRA &= ~(1 << ISC01);
				EICRA &= ~(1 << ISC00);
				EIMSK |= (1 << INT0);
			}
			else if(INT1 == int_type)
			{
				EICRA &= ~(1 << ISC11);
				EICRA &= ~(1 << ISC10);
				EIMSK |= (1 << INT1);
			}
			else
			{
				//no implementation
			}
			break;
			
		case ANY:
			if(INT0 == int_type)
			{
				EICRA |= (1 << ISC00);
				EICRA &= ~(1 << ISC01);
				EIMSK |= (1 << INT0);
			}
			else if(INT1 == int_type)
			{
				EICRA |= (1 << ISC10);
				EICRA &= ~(1 << ISC11);
				EIMSK |= (1 << INT1);
			}
			else
			{
				//no implementation
			}
			break;
			
		case FALLING:
			if(INT0 == int_type)
			{
				//EICRA |= (1 << FALLING);
				EICRA |= (1 << ISC01);
				EICRA &= ~(1 << ISC00);
				EIMSK |= (1 << INT0);
			}
			else if(INT1 == int_type)
			{
				EICRA |= (1 << ISC11);
			    EICRA &= ~(1 << ISC10);
				EIMSK |= (1 << INT1);
			}
			else
			{
				//no implementation
			}
			break;
			
		case RISING:
			if(INT0 == int_type)
			{
				EICRA |= (1 << ISC01);
				EICRA |= (1 << ISC00);
				EIMSK |= (1 << INT0);
			}
			else if(INT1 == int_type)
			{
				EICRA |= (1 << ISC11);
				EICRA |= (1 << ISC10);
				EIMSK |= (1 << INT1);
			}
			else
			{
				//no implementation
			}
			break;
			
		default:
			break;
	}
	
	sei();
}

void GPIO_EXTINT_RESET(uint8_t int_type)
{
	if(INT0 == int_type)
	{
		EIMSK &= ~(1 << INT0);
	}
	else if(INT1 == int_type)
	{
		EIMSK &= ~(1 << INT1);
	}
	else
	{
		
	}
}