/*
 * power_factor_calc.c
 *
 * Created: 11/20/2023 1:55:25 PM
 *  Author: Dewmith
 */ 


#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include "phase_angle.h"
#include "power_factor.h"
#include "voltage_sensor.h"
#include "current_sensor.h"
#include "port_expander.h"

double voltage_value = 0;
double current_value = 0;
double power_angle_value = 0;

void get_measured_vals()
{
	voltage_value = get_voltage_rms();
	current_value = get_current_rms();
	power_angle_value = get_phase_angle();
}

double get_power_factor(void)
{
	return (cos(power_angle_value));
}


double get_active_power(void)
{
	return (current_value* voltage_value * 0.001 * get_power_factor());
}


double get_required_capacitive_reactance()
{
	return (get_active_power() * (tan(power_angle_value) - tan(0.1047)));
}

uint8_t shift_bit = 0;
void add_capacitor(uint8_t num_of_relays)
{
	for(uint8_t i = 0; i<num_of_relays; i++)
	{
		shift_bit |= 1<<i;
	}
	
	port_expander_set(shift_bit, MSB_FIRST);
}

double get_capacitance_val()
{
	static double temp = 0;
	temp = 2 * M_PI * 50 * square(voltage_value);
	return (get_required_capacitive_reactance() / temp);
}


void correct_power_factor()
{	
	static uint8_t num_of_relays = 0;
	num_of_relays = get_capacitance_val() / 1.2;	
	add_capacitor(num_of_relays);
}
