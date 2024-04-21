//Define all needed address BusReg to toggle a led attached pin5 on port B with proteus 8
#include 			"stm32f401xc.h"
#include            <stdio.h>
#include 			"uart.h"
#include 			"systick.h"
#include            "exti.h"

int __io_putchar(int ch){
	uart2_write(ch);
	return ch;
}
//static void exti_callback();
void main(void)
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;//set one at second field in RCC register to enable clock for register GPIO_PORT_A
	GPIOA->MODER |= (1UL<<10); // set 1 at position 10 (counting from 0) in GPIO_MODE_REGISETR to set pin5 port A as an output
	GPIOA->MODER &=~ (1UL<<11); //set 0 at position 11 (counting from 0) in GPIO_MODE_REGISETR to set pin5 port A as an output
	
	uart2_rxtx_init();
	pa4_exti_init();
	while (1){
		printf("No Interruption ...\n\r");
		//GPIOA->ODR ^= (1UL<<5);
		systicDelayMs(1000);
	}
}
static void exti_callback(){
	printf("BTN pressed ... \n\r");
	GPIOA->ODR ^= (1UL<<5);
	systicDelayMs(1000);
}
// Name should be exactly the same as defined on startup code in g_pfnVectors and should be void (void)
void EXTI4_IRQHandler(void){
	//printf("In interruption");
	while ((EXTI->PR & LINE4) != 0){
		//Clear PR flag
		EXTI->PR |= LINE4;
		//callback
		exti_callback();
	}
}
/*#include "stm32f401xc.h"
#include "systick.h"
int main(){
	__disable_irq();
	RCC->AHB1ENR |= 1;
	RCC->AHB1ENR |= 4;
	RCC->APB2ENR |= 0X4000;
	GPIOA->MODER |= 0x400;
	SYSCFG->EXTICR[3] = 0x0020;
	EXTI->IMR |= 0x2000;
	EXTI->FTSR |= 0X2000;
	NVIC_EnableIRQ(EXTI15_10_IRQn);
	__enable_irq();
	while(1){}
}
void EXTI15_10_IRQHandler(void){
	GPIOA->BSRR = 0x20;
	systicDelayMs(400);
	GPIOA->BSRR = 0x002;
	systicDelayMs(400);
	GPIOA->BSRR = 0x20;
	systicDelayMs(400);
	GPIOA->BSRR = 0x002;
	systicDelayMs(400);
	EXTI->PR = 0x2000;
}*/
