/*
 * Timer.h
 *
 * Created: 9/8/2023 9:00:10 PM
 *  Author: Dewmith
 */ 

#ifndef TIMER_H_
#define TIMER_H_

#define T0 0
#define T1 1

/**
 * @brief  Intializes the Timer module      
 *
 */
void TIMER_MS_INIT();
void TIMER_US_INIT(); 
/**
 * @brief  This API returns the miliseconds elapsed since the beginning of the MCU
 *
 * @return uint32_t - The time elapsed in miliseconds
 
 */
uint32_t millis();

uint32_t micros();

void disable_timer_INT(uint8_t timer);

void enable_timer_INT(uint8_t timer);

#endif /* TIMER_H_ */