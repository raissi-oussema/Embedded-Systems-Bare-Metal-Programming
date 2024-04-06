/*
 * exti.c
 *
 *  Created on: Apr 5, 2024
 *      Author: Oussema Raissi
 */
#include "exti.h"

void pc13_exti_init(void){
    /*Disable global interrupts*/ // Good practice
    __disable_irq();
    /*Enavle clock access for GPIOA*/
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    /*SET PA4 as input*/
    GPIOA->MODER &=~ GPIO_MODER_MODE4_0;
    GPIOA->MODER &=~ GPIO_MODER_MODE4_1;
    /*Enable clock access to SYSCONFIG*/
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
    /*Select PORTA for EXTI4*/
    SYSCFG->EXTICR[1] &=~ (1UL << 0);
    SYSCFG->EXTICR[1] &=~ (1UL << 1);
    SYSCFG->EXTICR[1] &=~ (1UL << 2);
    SYSCFG->EXTICR[1] &=~ (1UL << 3);
    /*Unmask EXTI4*/
    EXTI->IMR |= EXTI_IMR_IM4; // Ref manual for EXTI_IMR
    /*Select falling edge trigger*/ // you can try rising edge too
    EXTI->FTSR |= EXTI_FTSR_TR4;
    /*Enable EXTI line in NVIC*/
    NVIC_EnableIRQ(EXTI4_IRQn);
    /*Enable global interrupts*/
    __enable_irq();
}

