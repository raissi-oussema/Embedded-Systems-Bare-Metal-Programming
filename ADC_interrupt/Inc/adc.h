/*
 * adc.h
 *
 *  Created on: Mar 29, 2024
 *      Author: Oussema Raissi
 */

#ifndef ADC_H_
#define ADC_H_
#include <stdint.h>

void pa1_adc_init(void);
uint32_t adc_read(void);
void start_conversion(void);
void pa1_adc_with_interrupt_init(void);

#endif /* ADC_H_ */
