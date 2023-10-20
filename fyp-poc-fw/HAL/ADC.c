/**
 * @file ADC.c
 * @author Dewmith Ranasinghe (dewmithrana@gmail.com)
 * @brief HAL level APIs to configure and read ADC channels
 * @version 0.1
 * @date 01-08-2023
 *  
 */

#include <avr/io.h>
#include <util/delay.h>
#include "ADC.h"

/**
 * @brief  Intializes the ADC module           
 *
 */
void ADC_INIT() {

    ADMUX |= (1 << REFS0);
    ADCSRA |= (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

/**
 * @brief  Reads the given channel and return the digital value      
 *
 * @param  channel(uint8_t)- The ADC Channel to be read
 *
 * @return uint16_t - The converted adc_value
 */
uint16_t ADC_READ(uint8_t channel) {

    static uint16_t adc_value = 0;
    
    ADMUX = (ADMUX & 0xF8) | (channel & 0x07);   
    ADCSRA |= (1 << ADSC);    
    while (ADCSRA & (1 << ADSC));
    adc_value = ADCL | (ADCH << 8);
	
    return adc_value;
}

