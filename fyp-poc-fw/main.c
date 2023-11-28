/*
 * fyp-poc-fw.c
 *
 * Created: 10/14/2023 4:08:25 PM
 * Author : Dewmith
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "TWI.h"
#include "GPIO.h"
#include "UART.h"
#include "LCD.h"
#include "ADC.h"
#include "debug_utilis.h"
#include "phase_angle.h"
#include "Timer.h"
#include "voltage_sensor.h"
#include "current_sensor.h"
#include "power_factor.h"
#include "port_expander.h"

double voltage_val;
double current_val;
double power_factor;

char BUF[16];
void buzzer_beep()
{
	GPIO_WRITE_PIN(BUZZER_OUT_Pin, BUZZER_OUT_Port, SET);
	_delay_ms(1000);
	GPIO_WRITE_PIN(BUZZER_OUT_Pin, BUZZER_OUT_Port, RESET);
	_delay_ms(1000);
}

void buzzer_beep2()
{
	GPIO_WRITE_PIN(BUZZER_OUT_Pin, BUZZER_OUT_Port, SET);
	_delay_ms(200);
	GPIO_WRITE_PIN(BUZZER_OUT_Pin, BUZZER_OUT_Port, RESET);
	_delay_ms(200);
	GPIO_WRITE_PIN(BUZZER_OUT_Pin, BUZZER_OUT_Port, SET);
	_delay_ms(200);
	GPIO_WRITE_PIN(BUZZER_OUT_Pin, BUZZER_OUT_Port, RESET);
	_delay_ms(200);
	GPIO_WRITE_PIN(BUZZER_OUT_Pin, BUZZER_OUT_Port, SET);
	_delay_ms(200);
	GPIO_WRITE_PIN(BUZZER_OUT_Pin, BUZZER_OUT_Port, RESET);
	_delay_ms(200);
}

int main(void)
{
    /* Replace with your application code */
	UART_INIT();
	TWI_INIT(); 
	LCD_init();	
	ADC_INIT();
	port_expander_init();
	port_expander_set(0, MSB_FIRST);
	GPIO_SET_PIN(BUZZER_OUT_Pin, BUZZER_OUT_Port, OUTPUT);
    buzzer_beep();	
	phase_angle_init();
	voltage_sensor_init();
	current_sensor_init();

    while (1) 
    {
    
		LCD_clear();
		voltage_val = get_voltage_rms();
		current_val = get_current_rms();
		power_factor = get_power_factor();
		LCD_set_cursor(1,1);
		LCD_print("PF = ");
		LCD_set_cursor(1,6);
		LCD_print_float(power_factor);
		LCD_set_cursor(2,1);
		LCD_print("P = ");
		LCD_print_float(get_active_power());
		LCD_print(" W");
    
		debug_print("===========================\n\r");
		debug_print("voltage - ");
		debug_print_float(voltage_val);
		debug_print("\n\rcurrent- ");
		debug_print_float(current_val);
		debug_print("\n\rpower factor - ");
		debug_print_float(power_factor);
		debug_print("\n\ractive power - ");
		debug_print_float(get_active_power());
		debug_print("\n\required- ");
		debug_print_float(get_required_capacitive_reactance());
		debug_print("\n\rcapacitance - ");
		debug_print_float(get_capacitance_val());
		debug_print("\n\r");
		
	   _delay_ms(5000);
   
	   if(power_factor < 0.89)
	   {
			correct_power_factor();
			buzzer_beep2();
		
	   }   
		_delay_ms(2000);	
		
   }
}

