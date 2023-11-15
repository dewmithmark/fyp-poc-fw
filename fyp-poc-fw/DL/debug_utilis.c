/*
 * debug_utilis.c
 *
 * Created: 11/7/2023 12:54:06 PM
 *  Author: Dewmith
 */ 


#include "debug_utilis.h"
#include "util/delay.h"
#include "UART.h"


/**
 * @brief 
 *
 */
void debug_print_float(float value)
{
	int integer_part = (int)value;
	int decimal_part = (int)((value - integer_part) * 1000); // Extract 3 decimal places	
	sprintf(BUFFER, "%d.%d", integer_part, decimal_part);
	debug_print(BUFFER);
}

PUTCHAR_PROTOTYPE
{
	UART_TRANSMIT((uint8_t)ch);
	return ch;
}

void debug_print(const char *message)
{
	for (int i = 0; message[i] != '\0'; i++) {
		UART_TRANSMIT(message[i]);
		_delay_ms(10); 
	}
}