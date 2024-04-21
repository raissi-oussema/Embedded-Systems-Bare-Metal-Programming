/* Define all needed address BusReg to toggle a led attached pin5 on port B with proteus 8*/
#include "stm32f401xc.h"
#include <stdint.h>
#include "uart.h"


char str;
static void uart_callback(void);


void main(void){
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	GPIOA->MODER |= (1UL<<10); 
	GPIOA->MODER &=~ (1UL<<11);
	
	uart2_rx_interrupt_init();

	while (1) {}
	
}
static void uart_callback(void){
		str = USART2->DR;
		if (str=='1'){
			GPIOA->ODR |= (1<<5);
		}
		else{
			GPIOA->ODR &=~ (1<<5);
		}
}
void USART2_IRQHandler(void){
	//check if RXNE is set
	if (USART2->SR & USART_SR_RXNE){
		//if we enter '1' the led will toggle else it will not
		uart_callback();
	}
}
