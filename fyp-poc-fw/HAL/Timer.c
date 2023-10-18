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
static void disable_timer0_INT();
static void enable_timer0_INT();

/**
 * @brief  Intializes the Timer module      
 *
 */
void TIMER_INIT() {
		
	TCCR0A = 0;
	TCCR0B = 0;
	TCCR0B |= (1 << CS01) | (1 << CS00);
	TCNT0 = 6;
	TIMSK0 |= (1 << TOIE0);
}

static void disable_timer0_INT()
{
	TIMSK0 &= ~(1 << TOIE0);
}
static void enable_timer0_INT()
{
	TIMSK0 |= (1 << TOIE0);
}

/**
 * @brief  This API returns the milliseconds elapsed since the beginning of the MCU
 *
 * @return uint32_t - The time elapsed in milliseconds
 */
uint32_t millis()
{
	static uint32_t ms = 0;
	disable_timer0_INT();
	ms = millis_counter;
	enable_timer0_INT();
	return ms;
}

/**
 * @brief  The interrupt service routine of TIMER          
 *
 */
ISR(TIMER0_OVF_vect)
{
	millis_counter++;
}