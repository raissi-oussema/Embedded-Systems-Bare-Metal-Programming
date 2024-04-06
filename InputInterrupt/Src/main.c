/* Define all needed address BusReg to toggle a led attached pin5 on port B with proteus 8*/
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
	pc13_exti_init();
	while (1){}
}
static void exti_callback(){
	printf("BTN pressed ... \n\r");
	GPIOA->ODR ^= (1UL<<5);
	//systicDelayMs(1000);
}
// Name should be exactly the same as defined on startup code in g_pfnVectors and should be void (void)
void EXTI4_IRQHandler(void){
	printf("In interruption");
	while ((EXTI->PR & LINE4) != 0){
		//Clear PR flag
		EXTI->PR |= LINE4;
		//callback
		exti_callback();
	}
	
}
