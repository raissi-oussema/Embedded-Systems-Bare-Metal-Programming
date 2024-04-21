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
	 *we cannot devide directly by 1 000 000 because reg is just 16 bit register
	 *so we devide by 1111 1111 1111 1111 = 65535 - 1
	 */
	TIM2->PSC = 65535 - 1;
	/*Set auto reload value*/
	/*
	 *Now the frequence is 15hz 
	 * we need to count 15 step from 15hz to got frequency of 1hz ,then relaod the counter
	 */
	TIM2->ARR = 244 - 1;
	/*Clear counter*/
	TIM2->CNT = 0;
	/*Enable timer*/
	TIM2->CR1 = TIM_CR1_CEN;
}
