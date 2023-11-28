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


/**
 * @brief function prototypes for linking UART protocol with printf syntax
 *
 */

void debug_print_float(float value);

void debug_print(char *message);


#endif /* DEBUG_UTILIS_H_ */

