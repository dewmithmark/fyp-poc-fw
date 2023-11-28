/*
 * current_sensor.c
 *
 * Created: 11/17/2023 12:48:08 PM
 *  Author: Dewmith
 */ 

#include <util/delay.h>
#include <stdint.h>
#include "current_sensor.h"
#include "debug_utilis.h"
#include "GPIO.h"
#include "ADC.h"

#define NUM_OF_SAMPLES 200
uint16_t max_raw_curr_val = 100;
uint16_t min_raw_curr_val = 1023;

void current_sensor_init()
{
	GPIO_SET_PIN(CURRENT_SENSOR_OUT_Pin, CURRENT_SENSOR_OUT_Port, INPUT);
}

uint16_t get_current_pp()
{
	static uint16_t raw_current_val = 0;
	max_raw_curr_val = 0;
	min_raw_curr_val = 1023;
	
	for(uint8_t i=0; i<NUM_OF_SAMPLES; i++)
	{
		raw_current_val = ADC_READ(CURRENT_SENSOR_OUT_Channel);
		if(raw_current_val >= max_raw_curr_val)
		{
			max_raw_curr_val = raw_current_val;
		}
		
		if(raw_current_val <= min_raw_curr_val)
		{
			min_raw_curr_val = raw_current_val;
		}
		
		_delay_us(10);
	}
	
	//sprintf(BUFFER, " %d , %d \n\r", max_raw_curr_val , min_raw_curr_val) ;
	//debug_print(BUFFER);
	//debug_print_float(max_raw_curr_val - min_raw_curr_val);
	return (max_raw_curr_val - min_raw_curr_val);
}
double actual_currrent_pp_ = 0;
double actual_currrent_pp = 0;
double get_current_rms()
{
	for(uint8_t i = 0; i < 10; i++)
	{
		actual_currrent_pp += ((double)get_current_pp() * 5000.0)/1023.0;
	}
	actual_currrent_pp /= 10.0;
	return (actual_currrent_pp * 353.553)/215.0 ;
}