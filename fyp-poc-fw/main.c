/*
 * fyp-poc-fw.c
 *
 * Created: 10/14/2023 4:08:25 PM
 * Author : Dewmith
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "GPIO.h"
#include "UART.h"
int main(void)
{
    /* Replace with your application code */
	UART_INIT();
	GPIO_SET_PIN(BUZZER_OUT_Pin, BUZZER_OUT_Port, OUTPUT);
    while (1) 
    {
		GPIO_WRITE_PIN(BUZZER_OUT_Pin, BUZZER_OUT_Port, SET);
		_delay_ms(100);
		GPIO_WRITE_PIN(BUZZER_OUT_Pin, BUZZER_OUT_Port, RESET);
		_delay_ms(100);
		UART_TRANSMIT(65);
		_delay_ms(100);
    }
}

