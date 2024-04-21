#ifndef UART_STM32F1_H_
#define UART_STM32F1_H_
#include <stdint.h>
#include "stm32f103xb.h"

void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t Baudrate);
uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t Baudrate);
void uart2_rxtx_init(void);
char uart_read(void);
void uart2_write(int ch);

#endif // !1
