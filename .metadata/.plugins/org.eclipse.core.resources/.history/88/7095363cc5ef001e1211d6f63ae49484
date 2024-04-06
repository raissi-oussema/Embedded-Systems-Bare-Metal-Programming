/*
 * tim.c
 *
 *  Created on: Mar 31, 2024
 *      Author: Oussema Raissi
 */
#include "stm32f401xc.h"
void tim2_1hz_init(void){
	/*Enable clock access to tim2*/
	//tim2 is connected to apb1 bud
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	/*Set prescalar value*/
	/*
	 *system clock = 1Mhz; for 1hz we need to divide 1 000 000  / 1 000 000 = 1hz
	 *we cannot devide directly by 1 000 000 because reg is just 16 bit registre
	 *so we devide by 1111 1111 1111 1111 = 65535 - 1
	 */
	TIM2->PSC = 65535 - 1;
	/*Set auto reload value*/
	/*
	 *Now the frequence is 15hz 
	 * we need to count 15 step from 15hz to got frequency of 1hz ,then relaod the counter
	 */
	TIM2->ARR = 15 - 1;
	/*Clear counter*/
	TIM2->CNT = 0;
	/*Enable timer*/
	TIM2->CR1 = TIM_CR1_CEN;
}
void tim2_pa5_compare_mode(void){

	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;//set one at second field in RCC register to enable clock for register GPIO_PORT_B

	GPIOA->MODER &=~GPIO_MODER_MODE5_0; // set Pin 5 to alternate function mode
	GPIOA->MODER |= GPIO_MODER_MODE5_1;

	/*SET PA5 to alternate function type TIM2_CH1 (AF01)*/
	GPIOA->AFR[0] |= GPIO_AFRL_AFRL5_0; // [0] because we are dealing with Low reg
	/*Enable clock access to tim2*/
	//tim2 is connected to apb1 bud
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	/*Set prescalar value*/
	/*
	 *system clock = 1Mhz; for 1hz we need to divide 1 000 000  / 1 000 000 = 1hz
	 *we cannot devide directly by 1 000 000 because reg is just 16 bit registre
	 *so we devide by 1111 1111 1111 1111 = 65535 - 1
	 */
	TIM2->PSC = 65535 - 1;
	/*Set auto reload value*/
	/*
	 *Now the frequence is 15hz 
	 * we need to count 15 step from 15hz to got frequency of 1hz ,then relaod the counter
	 */
	TIM2->ARR = 15 - 1;
	/*Clear counter*/

	/*Configure output compare Mode for channel one to toggle ; TIMx capture/compare mode register 1 */
	TIM2->CCMR1 |= TIM_CCMR1_OC1M_0;
	TIM2->CCMR1 |= TIM_CCMR1_OC1M_1;
	TIM2->CCMR1 &=~TIM_CCMR1_OC1M_2;
	/*Enable capture compare mode*/
	TIM2->CCER |= TIM_CCER_CC1E;

	TIM2->CNT = 0;
	/*Enable timer*/
	TIM2->CR1 = TIM_CR1_CEN;
}
