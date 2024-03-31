/* Define all needed address BusReg to toggle a led attached pin5 on port B with proteus 8*/
#include "stm32f401xc.h"
#include <stdint.h>
#include "uart.h"

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
