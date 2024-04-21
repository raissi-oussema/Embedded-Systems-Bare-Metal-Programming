/*
 * systic.c
 *
 *  Created on: Mar 30, 2024
 *      Author: Oussema Raissi
 */
#include "stm32f401xc.h"
#define SYSTICK_LOAD_VALUE (16000000UL)


void systicDelayMs(int delay){
    //refer to arm cortexm4 userguide
    /*****Configure systic********/
    /*Relaod systic value by needed time to count*/
    SysTick->LOAD = delay * SYSTICK_LOAD_VALUE;
    /*Clear systick current value reg*/
    SysTick->VAL = 0;
    /*Enable systick and select clock source*/
    SysTick->CTRL = ((SysTick_CTRL_ENABLE_Msk << SysTick_CTRL_ENABLE_Pos) | SysTick_CTRL_CLKSOURCE_Msk);
    //SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;

    while ((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk)==0){} 
    
    SysTick->CTRL = 0;
}

