/*
 * port_expander.h
 *
 * Created: 11/17/2023 2:55:09 PM
 *  Author: Dewmith
 */ 


#ifndef PORT_EXPANDER_H_
#define PORT_EXPANDER_H_

#include <stdint.h>


#define MSB_FIRST 1
#define LSB_FIRST 2

/**
 * @brief Initialization of shift register
 *
 */
void port_expander_init();

/**
 * @brief To shift in 8 bits
 *
 * @param data_in - 8 bit data value
 * @param mode - MSB_FIRST To shift the data byte starting from the most significant bit
 * 				 LSB_FIRST To shift the data byte starting from the least significant bit
 */
void port_expander_set(uint8_t data_in, uint8_t mode);


#endif /* PORT_EXPANDER_H_ */