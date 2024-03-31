/* Define all needed address BusReg to toggle a led attached pin5 on port B with proteus 8*/
#include 			"stm32f401xc.h"
#include 			"adc.h"
#include            <stdio.h>
#include 			"uart.h"

int __io_putchar(int ch){
	uart2_write(ch);
	return ch;
}
uint32_t value;
void main(void)
{
	pa1_adc_init();
	uart2_rxtx_init();

	while (1){
		start_conversion();
		value = adc_read();
		printf ("the value is %d \n\r",(int)value);
		for (int i=0; i<1000000;i++){}
		//uart2_write(value);
	}
}
