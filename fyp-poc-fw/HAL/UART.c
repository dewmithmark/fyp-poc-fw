/**
 * @file UART.c
 * @author Dewmith Ranasinghe (dewmithrana@gmail.com)
 * @brief 
 * @version 0.1
 * @date 01-08-2023
 *  
 */

#include <avr/io.h>
#include <util/delay.h>
#include "UART.h"

#define F_CPU 16000000UL
#define	UBRR_VALUE ((F_CPU / (BAUD_RATE * 16UL)) - 1)

/**
 * @brief Initializes the UART module.
 *
 */
void UART_INIT() 
{	
	UBRR0H = (uint8_t)(UBRR_VALUE >> 8);
	UBRR0L = (uint8_t)(UBRR_VALUE);	
	UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);
}

/**
 * @brief Transmits a packet of 8-bit data over the USART peripheral.
 *
 * @param data(uint8_t) - The 8-bit data packet to be transmitted.
 */
void UART_TRANSMIT(uint8_t data) 
{
	while (!(UCSR0A & (1 << UDRE0)));
	UDR0 = data;
}

