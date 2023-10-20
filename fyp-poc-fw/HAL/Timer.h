/*
 * Timer.h
 *
 * Created: 9/8/2023 9:00:10 PM
 *  Author: Dewmith
 */ 

#ifndef TIMER_H_
#define TIMER_H_

/**
 * @brief  Intializes the Timer module      
 *
 */
void TIMER_INIT();

/**
 * @brief  This API returns the miliseconds elapsed since the beginning of the MCU
 *
 * @return uint32_t - The time elapsed in miliseconds
 */
uint32_t millis();

#endif /* TIMER_H_ */