/*
 * debug_utilis.h
 *
 * Created: 11/7/2023 12:53:49 PM
 *  Author: Dewmith
 */ 


#ifndef DEBUG_UTILIS_H_
#define DEBUG_UTILIS_H_

#include <stdio.h>
#include <avr/io.h>

#ifdef _GNUC_
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif

/**
 * @brief function prototypes for linking UART protocol with printf syntax
 *
 */

void debug_print_float(float value);

void debug_print( const char *message);


#endif /* DEBUG_UTILIS_H_ */

