/* Define all needed address BusReg to toggle a led attached pin5 on port B with proteus 8*/
#include 			"stm32f401xc.h"
#include 			"tim.h"
#include            <stdio.h>
#include 			"uart.h"


int __io_putchar(int ch){
	uart2_write(ch);
	return ch;
}
void main(void)
{
	tim2_pa5_compare_mode();
	while (1){}
}
