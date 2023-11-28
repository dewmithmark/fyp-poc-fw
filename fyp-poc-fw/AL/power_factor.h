/*
 * power_factor_calc.h
 *
 * Created: 11/20/2023 1:59:42 PM
 *  Author: Dewmith
 */ 


#ifndef POWER_FACTOR_H_
#define POWER_FACTOR_H_

double get_power_factor();

double get_active_power();


double get_required_capacitive_reactance();


double get_capacitance_val();

void correct_power_factor();

#endif /* POWER_FACTOR_H_ */