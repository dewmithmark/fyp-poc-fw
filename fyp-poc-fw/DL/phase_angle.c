/*
 * phase_angle.c
 *
 * Created: 11/7/2023 1:14:06 PM
 *  Author: Dewmith
 */

#include <util/delay.h>
#include <math.h>
#include "GPIO.h" 
#include "Timer.h"
#include "debug_utilis.h"

#define TIMEOUT 200000
#define NUM_OF_SAMPLES 10
unsigned long start_time = 0 ;
unsigned long end_time = 0;
uint32_t duration;
uint8_t sample_counter = 0;

void phase_diff_measure();

void phase_angle_init()
{
	GPIO_SET_PIN(ZCD_IN_Pin, ZCD_IN_Port, INPUT);
	TIMER_US_INIT();	
}

double get_phase_angle()
{	
	enable_timer_INT(T1);
	for(sample_counter = 0; sample_counter < NUM_OF_SAMPLES; sample_counter++)
	{
		phase_diff_measure();
	}
    disable_timer_INT(T1);	
	duration /= NUM_OF_SAMPLES;
	//sprintf(BUFFER, "duration = %ld  ", duration);
	//debug_print(BUFFER);
		
	return ((duration * 2 * M_PI)/20000);
	
}

void  phase_diff_measure(void) 
{	
	while(RESET == GPIO_READ_PIN(ZCD_IN_Pin , ZCD_IN_Port));
	start_time = micros();	
	while(SET == GPIO_READ_PIN(ZCD_IN_Pin , ZCD_IN_Port));
	end_time = micros();   
	if (micros()- start_time > TIMEOUT)
    {
		duration =  0; 
	}
	duration +=  (end_time - start_time) ;
	
}

