/*
 * GPIO.h
 *
 * Created: 8/11/2023 9:48:52 AM
 *  Author: Dewmith
 */ 
#ifndef GPIO_H_
#define GPIO_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <stdint.h>

enum _PORTS
{
	_PORTB = 1,
	_PORTC,
	_PORTD
};

#define INPUT			0
#define OUTPUT			1
#define INPUT_PULLUP	2

#define LOW		0
#define ANY		1
#define FALLING	2
#define RISING	3

#define RESET	0
#define SET		1


#define ZCD_IN_Pin					PORTD2
#define ZCD_IN_Port					_PORTD
#define ZCD_IN_INT					INT0 
#define VOLTAGE_CHECK_IN_Pin		PORTB1
#define VOLTAGE_CHECK_IN_Port		_PORTB
#define CURRENT_CHECK_IN_Pin		PORTB2
#define CURRENT_CHECK_IN_Port		_PORTB
#define SHIFT_REG_DIN_OUT_Pin		PORTB0
#define SHIFT_REG_DIN_OUT_Port		_PORTB
#define SHIFT_REG_CLK_OUT_Pin		PORTD7
#define SHIFT_REG_CLK_OUT_Port		_PORTD
#define SHIFT_REG_LATCH_OUT_Pin		PORTD6
#define SHIFT_REG_LATCH_OUT_Port	_PORTD
#define SHIFT_REG_RESET_OUT_Pin		PORTD5
#define SHIFT_REG_RESET_OUT_Port	_PORTD
#define BUZZER_OUT_Pin				PORTD4
#define BUZZER_OUT_Port				_PORTD
#define PUSH_BUTTON_IN_Port			PORTD3
#define PUSH_BUTTON_IN_Pin			_PORTD
#define PUSH_BUTTON_IN_INT			INT1
#define VOLTAGE_SENSOR_OUT_Pin		PORTC0
#define VOLTAGE_SENSOR_OUT_Port		_PORTC
#define VOLTAGE_SENSOR_OUT_Channel	0
#define CURRENT_SENSOR_OUT_Pin		PORTC1
#define CURRENT_SENSOR_OUT_Port		_PORTC
#define CURRENT_SENSOR_OUT_Channel	1

 
/**
 * @brief 
 *
 * @param
 *
 * @retval
 */
void GPIO_SET_PIN(uint8_t pin, uint8_t port, uint8_t status);

/**
 * @brief 
 *
 * @param
 *
 * @retval
 */
void GPIO_WRITE_PIN(uint8_t pin, uint8_t port, uint8_t status);

/**
 * @brief 
 *
 * @param
 *
 * @retval
 */
uint8_t GPIO_READ_PIN(uint8_t pin, uint8_t port);

/**
 * @brief 
 *
 * @param
 *
 * @retval
 */
void GPIO_PCINT_SET(uint8_t pin, uint8_t port);

/**
 * @brief 
 *
 * @param
 *
 * @retval
 */
void GPIO_EXTINT_SET(uint8_t int_type, uint8_t trigger_edge, void (*isr_linker)(void));

/**
 * @brief 
 *
 * @param
 *
 * @retval
 */
void GPIO_EXTINT_RESET(uint8_t int_type);
      


#endif /* GPIO_H_ */