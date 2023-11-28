/**
 * @file    voltage_sensor.c
 * @author  Dewmith R (dewmithr@zone24x7.com)
 * @brief   
 * @version 0.1
 * @date   
 *
 * @copyright Copyright (c) 2022
 *
 */
#define NUM_OF_SAMPLES 200

#include <util/delay.h>
#include <stdint.h>
#include "voltage_sensor.h"
#include "debug_utilis.h"
#include "GPIO.h"
#include "ADC.h"

uint16_t max_raw_val = 0;
uint16_t min_raw_val = 1023;
	
void voltage_sensor_init()
{
	GPIO_SET_PIN(VOLTAGE_SENSOR_OUT_Pin, VOLTAGE_SENSOR_OUT_Port, INPUT);
}

uint16_t get_voltage_pp()
{
	static uint16_t raw_voltage_val = 0;
	max_raw_val = 0;
	min_raw_val = 1023;
	
	for(uint8_t i=0; i<NUM_OF_SAMPLES; i++)
	{		
		raw_voltage_val = ADC_READ(VOLTAGE_SENSOR_OUT_Channel);
		if(raw_voltage_val >= max_raw_val)
		{
			max_raw_val = raw_voltage_val;			
		}
		
		if(raw_voltage_val <= min_raw_val)
		{
			min_raw_val = raw_voltage_val;
		}
		
		_delay_us(10);		
	}
	
	//sprintf(BUFFER, " %d , %d \n\r", max_raw_val , min_raw_val) ;
	//debug_print(BUFFER);
    //debug_print_float(max_raw_val - min_raw_val);
	return (max_raw_val - min_raw_val);
}
double actual_voltage_pp_ = 0;
double actual_voltage_pp = 0;
double get_voltage_rms()
{    
	 for(uint8_t i = 0; i < 10; i++)
	 {
		 actual_voltage_pp += ((double)get_voltage_pp() * 5000.0)/1023.0;
	 }	 
	 actual_voltage_pp /= 10000.0;
	return actual_voltage_pp * 0.35355 * 0.8986 * 230;
}