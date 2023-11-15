/*
 * Timer.c
 *
 * Created: 9/8/2023 9:00:34 PM
 *  Author: Dewmith
 */ 
#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "Timer.h"


uint32_t millis_counter = 0;
uint32_t micros_counter = 0;


/**
 * @brief  Intializes the Timer module      
 *
 */
void TIMER_MS_INIT() 
{		
	cli();
	TCCR0A = 0;
	TCCR0B = 0;
	TCCR0B |= (1 << CS01) | (1 << CS00);
	TCNT0 = 6;	
	sei();
}

void TIMER_US_INIT() 
{	
  cli(); 
  TCCR1A = 0; 
  TCCR1B = 0; 
  TCCR1B |= (1 << WGM12) | (1 << CS10); 
  OCR1A = 160 - 1;
  sei();
}


void disable_timer_INT(uint8_t timer)
{
	if(T1 == timer)
	{
		TIMSK1 &= ~(1 << OCIE1A);
	}
	if(T0 == timer)
	{
		TIMSK0 &= ~(1 << TOIE0);
	}
	
}
void enable_timer_INT(uint8_t timer)
{
	
	if(T1 == timer)
	{
		TIMSK1 |= (1 << OCIE1A);
	}
	if(T0 == timer)
	{
		TIMSK0 |= (1 << TOIE0);
	}
}

/**
 * @brief  This API returns the milliseconds elapsed since the beginning of the MCU
 *
 * @return uint32_t - The time elapsed in milliseconds
 */
uint32_t millis()
{
	static uint32_t ms = 0;
	disable_timer_INT(T0);
	ms = millis_counter;
	enable_timer_INT(T0);
	return ms;
}

uint32_t micros()
{
	static uint32_t us = 0;
	disable_timer_INT(T1);
	us = micros_counter;
	enable_timer_INT(T1);
	return us;	
}

/**
 * @brief  The interrupt service routine of TIMER          
 *
 */
ISR(TIMER0_OVF_vect)
{
	millis_counter++;
}

ISR(TIMER1_COMPA_vect) {
	
	micros_counter += 10;
}