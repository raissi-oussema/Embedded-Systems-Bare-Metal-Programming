#include "uart_stm32f1.h"

#define             SYS_FREQ		8000000
#define 			APB1_CLK		SYS_FREQ
#define 			UART_BAUDRATE	115200

void uart2_rxtx_init(void){
	/************Configure uart_gpio_pin***************/
	/*Enable clock for gpioa*/
	RCC->APB2ENR |= (2UL<<1);
	//RCC->AHB1ENR |= GPIOAEN;

	GPIOA->CRL |= GPIO_CRL_MODE1_1 | GPIO_CRL_MODE1_0;  // 0b11 50MHz output
    GPIOA->CRL |= GPIO_CRL_CNF1_1;    // PA9: output @ 50MHz - Alt-function Push-pull
    GPIOA->CRL |= GPIO_CRL_CNF2_0; 
	
	/************Configure uart module***************/
	/*Enable clock access to uart2*/
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
	/*Configure the baudrate*/
	uart_set_baudrate(USART2, APB1_CLK, UART_BAUDRATE);
	USART2->CR1 = USART_CR1_TE | USART_CR1_RE | USART_CR1_RXNEIE | USART_CR1_UE;
}

void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t Baudrate){
	USARTx->BRR = compute_uart_bd(PeriphClk, Baudrate);
}
uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t Baudrate){
	return (PeriphClk + (Baudrate/2U))/Baudrate;
}
void uart2_write(int ch){
	/*Make sure that transmit data register is empty*/
	while (!(USART2->SR & USART_SR_TXE)){}; // read status register TXE bit
	/*write to transmit data reg*/
	USART2->DR = (ch & 0xFF);
}
char uart_read(void){
	while (!(USART2->SR & USART_SR_RXNE)){}
	return USART2->DR;
}
