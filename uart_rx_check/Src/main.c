/* Define all needed address BusReg to toggle a led attached pin5 on port B with proteus 8*/
#include 			"stm32f401xc.h"
#include 			<stdint.h>
#define 			GPIOAEN			(1U<<0)
//Enable apb1 bus where uart module is connected (reference manual)
#define 			UART2EN			(1U<<17)

#define             SYS_FREQ		16000000
#define 			APB1_CLK		SYS_FREQ
#define 			UART_BAUDRATE	115200

//enable transmitter from refmanu(uasart_cr1 (contriol reg) bit number 3)
#define             CR1_TE			(1U<<3)
#define             CR1_UE			(1U<<13)//enable USART module
#define 			SR_TXE          (1U<<7) // status register TXE (page 548)


static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t Baudrate);
static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t Baudrate);
void uart2_rxtx_init(void);
char uart_read(void);
void uart2_write(int ch);

void main(void)
{
	uart2_rxtx_init();
	while (1)
	{
		char str = uart_read();
		if (str=='A'){
			uart2_write('A');
		}
	}
	
}
void uart2_rxtx_init(void){
	/************Configure uart_gpio_pin***************/
	/*Enable clock for gpioa*/
	RCC->AHB1ENR |= GPIOAEN;


	/*SET PA2 mode to alternate function mode(port a , pin2)*/
	GPIOA->MODER &=~ (1U<<4);
	GPIOA->MODER |= (1U<<5);
	/*SET PA2 alternate function type to UART_TX (AF7: in data sheet UART_2_TX and PA2 --> af7) (reference manual GPIO alternate function*/
	GPIOA->AFR[0]|= (1U<<8);//0 for low register 1 for hight reg
	GPIOA->AFR[0]|= (1U<<9);
	GPIOA->AFR[0]|= (1U<<10);
	GPIOA->AFR[0]&=~ (1U<<11);



	/*SET PA3 mode to alternate function mode(port a , pin3)*/
	GPIOA->MODER &=~ (1U<<6);
	GPIOA->MODER |= (1U<<7);
	/*SET PA2 alternate function type to UART_RX (AF7: in data sheet UART_2_RX and PA3 --> af7) (reference manual GPIO alternate function*/
	GPIOA->AFR[0]|= (1U<<12);//0 for low register 1 for hight reg
	GPIOA->AFR[0]|= (1U<<13);
	GPIOA->AFR[0]|= (1U<<14);
	GPIOA->AFR[0]&=~ (1U<<15); // 0111:AF7 should be configured (look datasheet) Alternate function mapping (continued)
	
	
	/************Configure uart module***************/
	/*Enable clock access to uart2*/
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
	/*Configure the baudrate*/
	uart_set_baudrate(USART2, APB1_CLK, UART_BAUDRATE);
	/*Configure the transfer direction RX TX*/
	USART2->CR1 = (USART_CR1_RE | USART_CR1_TE);
	/*Enable uart module*/
	USART2->CR1 |= USART_CR1_UE ;
}

static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t Baudrate){
	USARTx->BRR = compute_uart_bd(PeriphClk, Baudrate);
}
static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t Baudrate){
	return (PeriphClk + (Baudrate/2U))/Baudrate;
}
void uart2_write(int ch){
	/*Make sure that transmit data register is empty*/
	while (!(USART2->SR & SR_TXE)){}; // read status register TXE bit
	/*write to transmit data reg*/
	USART2->DR = (ch & 0xFF);
}
char uart_read(void){
	while (!(USART2->SR & USART_SR_RXNE)){}
	return USART2->DR;
}
