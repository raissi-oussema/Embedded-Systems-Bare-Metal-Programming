#ifndef UART_H_
#define UART_H_
#include <stdint.h>
#include "stm32f401xc.h"

void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t Baudrate);
uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t Baudrate);
void uart2_rxtx_init(void);
char uart_read(void);
void uart2_write(int ch);
void uart2_rx_interrupt_init(void);

#endif // !1