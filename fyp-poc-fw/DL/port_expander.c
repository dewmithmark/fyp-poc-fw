/*
 * port_expander.c
 *
 * Created: 11/17/2023 2:47:25 PM
 *  Author: Dewmith
 */ 

#include <util/delay.h>
#include "debug_utilis.h"
#include "port_expander.h"
#include "GPIO.h"

#define LOW		0
#define HIGH	1



static void clock_databit();
static void latch_pin(uint8_t status);
static void clock_pin(uint8_t status);
static void data_pin(uint8_t status);

/**
 * @brief Initialization of shift register
 *
 */
void port_expander_init()
{
	GPIO_SET_PIN(SHIFT_REG_DIN_OUT_Pin, SHIFT_REG_DIN_OUT_Port, OUTPUT);
	GPIO_SET_PIN(SHIFT_REG_CLK_OUT_Pin, SHIFT_REG_LATCH_OUT_Port, OUTPUT);
	GPIO_SET_PIN(SHIFT_REG_LATCH_OUT_Pin, SHIFT_REG_DIN_OUT_Port, OUTPUT);
	latch_pin(LOW);
	clock_pin(LOW);
	
	//data_pin(HIGH);
		//_delay_ms(2000);
		data_pin(LOW);
}

/**
 * @brief To shift in 8 bits
 *
 * @param data_in - 8 bit data value
 * @param mode - MSB_FIRST To shift the data byte starting from the most significant bit
 * 				 LSB_FIRST To shift the data byte starting from the least significant bit
 */
void port_expander_set(uint8_t data_in, uint8_t mode)
{
	uint8_t check_byte = 0;
	int8_t bit_pos = 0;

	latch_pin(LOW);
	clock_pin(LOW);

	if(mode == MSB_FIRST)
	{
		for(bit_pos = 7; bit_pos > -1; bit_pos--)
		{
			check_byte = data_in & (1 << bit_pos);

			if(check_byte)
			{
				data_pin(HIGH);
				clock_databit();
			}
			else
			{
				data_pin(LOW);
				clock_databit();
			}
		}
	}
	else if(mode == LSB_FIRST)
	{
		for(bit_pos = 0; bit_pos < 8; bit_pos++)
		{
			check_byte = data_in & (1 << bit_pos);

			if(check_byte)
			{
				data_pin(HIGH);
				clock_databit();
			}
			else
			{
				data_pin(LOW);
				clock_databit();
			}
		}
	}
	else
	{
		//No implementation
	}

	latch_pin(HIGH);
	_delay_ms(20);
	latch_pin(LOW);
}

/**
 * @brief pulse the clock signal
 *
 */
static void clock_databit()
{
	clock_pin(HIGH);
	_delay_ms(20);
	clock_pin(LOW);
}

/**
 * @brief Storage register pin status set
 *
 * @param status - HIGH 1
 * 				 - LOW 0
 */
static void latch_pin(uint8_t status)
{
	GPIO_WRITE_PIN(SHIFT_REG_LATCH_OUT_Pin, SHIFT_REG_DIN_OUT_Port, status);
}

/**
 * @brief serial clock pin status set
 *
 * @param status - HIGH 1
 * 				 - LOW 0
 */
static void clock_pin(uint8_t status)
{
	GPIO_WRITE_PIN(SHIFT_REG_CLK_OUT_Pin, SHIFT_REG_LATCH_OUT_Port, status);
}

/**
 * @brief data pin status set
 *
 * @param status - HIGH 1
 * 				 - LOW 0
 */
static void data_pin(uint8_t status)
{
	GPIO_WRITE_PIN(SHIFT_REG_DIN_OUT_Pin, SHIFT_REG_DIN_OUT_Port, status);
}
