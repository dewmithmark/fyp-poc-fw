/**
 * @file UART.h
 * @author Dewmith Ranasinghe (dewmithrana@gmail.com)
 * @brief 
 * @version 0.1
 * @date 01-08-2023
 *  
 */

#ifndef _UART_H_
#define _UART_H_

#define BAUD_RATE 9600

/**
 * @brief Initializes the UART module.
 *
 */
void UART_INIT();

/**
 * @brief Transmits a packet of 8-bit data over the USART peripheral.
 *
 * @param data(uint8_t) - The 8-bit data packet to be transmitted.
 */
void UART_TRANSMIT(uint8_t data);

#endif