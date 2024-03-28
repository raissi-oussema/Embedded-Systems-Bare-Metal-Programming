#include "stm32f401xc.h"
#include <stdint.h>
#define PERIPH_CLK  16000000
#define BAUDRATE    115200

void init_uart(void);
static void write_tx(int ch);

int main(){
    init_uart();
    while (1)
    {
        write_tx('H');
    }
    return 0;
}
/* USART2 is connected to APB1 BUS*/
void init_uart(void){

    /*******Configure PIN2 portA as internate function*********/
    /*Enable clock access to AHB1 port A*/
    RCC->AHB1ENR = RCC_AHB1ENR_GPIOAEN;
    /*Configure PA2 as ALTERNATE function pin*/
    GPIOA->MODER &=~ GPIO_MODER_MODER2_0;
    GPIOA->MODER |=  GPIO_MODER_MODER2_1;
    /*Alternate function section AF7 0111*/
    GPIOA->AFR[0] |=  GPIO_AFRL_AFSEL2_0;
    GPIOA->AFR[0] |=  GPIO_AFRL_AFSEL2_1;
    GPIOA->AFR[0] |=  GPIO_AFRL_AFSEL2_2;
    GPIOA->AFR[0] &=~ GPIO_AFRL_AFSEL2_3;


    /*Enable clock access to usart2 */
    RCC->APB1ENR = RCC_APB1LPENR_USART2LPEN; // shift to bit (1U << 17) 6.3.11 ref manual
    /*Enable tx mode*/
    USART2->CR1 = USART_CR1_TE;
    /*USART ENABLE*/
    USART2->CR1 |= USART_CR1_UE;
    /*Set baudrate*/
    USART2->BRR = (PERIPH_CLK + (BAUDRATE/2U))/BAUDRATE;

}
static void write_tx(int ch){
    while(!(USART2->SR & USART_SR_TXE)){};
    USART2->DR = (ch & 0xFF);
}
