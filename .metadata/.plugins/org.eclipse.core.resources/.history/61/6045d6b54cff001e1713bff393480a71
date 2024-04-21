/*
 * adc.c
 *
 *  Created on: Mar 29, 2024
 *      Author: Oussema Raissi
 */
#include "stm32f401xc.h"
#include "adc.h"

void pa1_adc_with_interrupt_init(void){
/*Enable clock access to GPIOA*/
RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
/*set the mode of PA1 to analog*/
GPIOA->MODER |= GPIO_MODER_MODE1_0;
GPIOA->MODER |= GPIO_MODER_MODE1_1;
/***Configure ADC module**/
/*Enable clock access a ADC module*/
RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
/*Enable ADC end of conversion interrupt*/
ADC1->CR1 |= ADC_CR1_EOCIE;
/*enable ADC interrupt in NVIC*/
NVIC_EnableIRQ(ADC_IRQn);
/**Configure ADC parametres**/

/*CONVERSION SEQUENECE start*/
ADC1->SQR3 |= ADC_SQR3_SQ1_0 ;
/*CONVERSION SEQUENCE lenght*/
ADC1->SQR1 &=~ (1UL<<20);
ADC1->SQR1 &=~ (1UL<<21);
ADC1->SQR1 &=~ (1UL<<22);
ADC1->SQR1 &=~ (1UL<<23);
/*Enable adc Module*/
ADC1->CR2 |= ADC_CR2_ADON;
__enable_irq();

}

void pa1_adc_init(void){
/*Enable clock access to GPIOA*/
RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
/*set the mode of PA1 to analog*/
GPIOA->MODER |= GPIO_MODER_MODE1_0;
GPIOA->MODER |= (1UL << 3);
/***Configure ADC module**/
/*Enable clock access a ADC module*/
RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
/**Configure ADC parametres**/

/*CONVERSION SEQUENECE start*/
ADC1->SQR3 |= ADC_SQR3_SQ1_0 ;
/*CONVERSION SEQUENCE lenght*/
ADC1->SQR1 &=~ (1UL<<20);
ADC1->SQR1 &=~ (1UL<<21);
ADC1->SQR1 &=~ (1UL<<22);
ADC1->SQR1 &=~ (1UL<<23);
/*Enable adc Module*/
ADC1->CR2 |= ADC_CR2_ADON;
}
void start_conversion(void){
    /*Enable this for continous convertion_mode and call start_conversion(); outside the loop in main*/
    ADC1->CR2 |= ADC_CR2_CONT;
    /*Start adc conversion*/
    ADC1->CR2 |= ADC_CR2_SWSTART;
}
uint32_t adc_read(void){
    /*wait for conversion to complete */
    while (!(ADC1->SR & ADC_SR_EOC)){}
    return (ADC1->DR);
}

