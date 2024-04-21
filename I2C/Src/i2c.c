#include "i2c.h"

void I2C1_init(void){
 /**
  * SET PB8---->SCL
  *     PB9---->SDA
  * Enable clock for GPIOB (1)
  * Configure PB8/PB9 to alternate function mode (af04) for i2c SCL and SDA (2)
  * configure PB8/PB9 to output open Drain (3)
  * Enable pull up for PB8/PB9 (4)
 */
RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN; //(1)

GPIOB->MODER &=~ GPIO_MODER_MODE8_0; //(2)
GPIOB->MODER |=  GPIO_MODER_MODE8_1;
GPIOB->MODER &=~ GPIO_MODER_MODE9_0;
GPIOB->MODER |=  GPIO_MODER_MODE9_1;

GPIOB->AFR[1] &=~ GPIO_AFRH_AFRH0_0;
GPIOB->AFR[1] &=~ GPIO_AFRH_AFRH0_1;
GPIOB->AFR[1] |=  GPIO_AFRH_AFRH0_2;
GPIOB->AFR[1] &=~ GPIO_AFRH_AFRH0_3;
GPIOB->AFR[1] &=~ GPIO_AFRH_AFRH1_0;
GPIOB->AFR[1] &=~ GPIO_AFRH_AFRH1_1;
GPIOB->AFR[1] |=  GPIO_AFRH_AFRH1_2;
GPIOB->AFR[1] &=~ GPIO_AFRH_AFRH1_3;

GPIOB->OTYPER |= GPIO_OTYPER_OT8;    //(3)
GPIOB->OTYPER |= GPIO_OTYPER_OT9;

GPIOB->PUPDR |=  GPIO_PUPDR_PUPD8_0; //(4)
GPIOB->PUPDR &=~ GPIO_PUPDR_PUPD8_1;
GPIOB->PUPDR |=  GPIO_PUPDR_PUPD9_0;
GPIOB->PUPDR &=~ GPIO_PUPDR_PUPD9_1;
/**
 * Enable clock for I2C1 			   (1)
 * Enter Reset Mode      			   (2)
 * Out of reset Mode     			   (3)
 * Set clock frequency to 16Mhz 	   (4)
 * set I2C to standard mode; 100kh clk (5)
 * set trize to 17					   (6)
 * Enable peripheral				   (7)
*/
RCC->APB1ENR |= RCC_APB1ENR_I2C1EN; //(1)
I2C1->CR1 	 |= I2C_CR1_SWRST;		//(2)
I2C1->CR1 	 &=~I2C_CR1_SWRST;		//(3)
I2C1->CR2    |= I2C_CR2_FREQ_4;		//(4)
I2C1->CCR    = 80;					//(5)
I2C1->TRISE  = 17;					//(6)
I2C1->CR1    |= I2C_CR1_PE;			//(7)
}

void I2C1_byteRead(char saddr, char maddr, char *data){
    volatile int temp;
    // Wait until bus is not busy
    while (I2C1->SR2 & I2C_SR2_BUSY){}
    // Genarate start condition
    I2C1->CR1 |= I2C_CR1_START;
    //wait until start flag is set
    while(!(I2C1->SR1 & I2C_SR1_SB)){}
    //transmit slave address + Write //first bit stay 0
    I2C1->DR = saddr << 1;
    //Wait until addr flag is set
    while(!(I2C1->SR1 & I2C_SR1_ADDR)){}
    //clear addr flag, Reading SR2 will clear the add flag
    temp = I2C1->SR2;
    //Send memory address
    I2C1->DR = maddr;
    //Wait until transmitter empty
    while(!(I2C1->SR1 & I2C_SR1_TXE)){}
    //generate restart
    I2C1->CR1 |= I2C_CR1_START;
    //wait until start flag is set
    while(!(I2C1->SR1 & I2C_SR1_SB)){}
    //Transmit salve addr + Read
    I2C1->DR = saddr << 1 | 1;
    //wait until address flag is set
    while(!(I2C1->SR1 & I2C_SR1_ADDR)){}
    //disable ack
    I2C1->CR1 &=~ I2C_CR1_ACK;
    //clear addr flag
    temp = I2C1->SR2;
    //Generate stop after data received
    I2C1->CR1 |= I2C_CR1_STOP;
    //wait until RXNE is set
    while(!(I2C1->SR1 & I2C_SR1_RXNE)){}
    //Read data from DR
    *data++ = I2C1->DR;
}
void I2C1_burstRead(char saddr, char maddr, int n, char *data){
    volatile int temp;
    // Wait until bus is not busy
    while (I2C1->SR2 & I2C_SR2_BUSY){}
    // Genarate start condition
    I2C1->CR1 |= I2C_CR1_START;
    //wait until start flag is set
    while(!(I2C1->SR1 & I2C_SR1_SB)){}
    //transmit slave address + Write //first bit stay 0
    I2C1->DR = saddr << 1;
    //Wait until addr flag is set
    while(!(I2C1->SR1 & I2C_SR1_ADDR)){}
    //clear addr flag, Reading SR2 will clear the add flag
    temp = I2C1->SR2;
    //Wait until transmitter empty
    while(!(I2C1->SR1 & I2C_SR1_TXE)){}
    //Send memory address
    I2C1->DR = maddr;
    //Wait until transmitter empty
    while(!(I2C1->SR1 & I2C_SR1_TXE)){}
    //generate restart
    I2C1->CR1 |= I2C_CR1_START;
    //wait until start flag is set
    while(!(I2C1->SR1 & I2C_SR1_SB)){}
    //Transmit salve addr + Read
    I2C1->DR = saddr << 1 | 1;
    //wait until address flag is set
    while(!(I2C1->SR1 & I2C_SR1_ADDR)){}
    //enable ack
    I2C1->CR1 &=~ I2C_CR1_ACK;
    while (n>0)
    {
        if (n==1)
        {
            //disable ack
            I2C1->CR1 &=~ I2C_CR1_ACK;  
            //Genarate stop
            I2C1->CR1 |= I2C_CR1_STOP;
            //wait until RXNE is set
            while(!(I2C1->SR1 & I2C_SR1_RXNE)){}
            //Read data from DR
            *data++ = I2C1->DR;
            break;
        }
        else
        {
            while(!(I2C1->SR1 & I2C_SR1_RXNE)){}
            (*data++) = I2C1->DR;
            n--;
        }
    }
    
}
void I2C1_burstWrite(char saddr, char maddr, int n, char *data){
    volatile int temp;
    // Wait until bus is not busy
    while (I2C1->SR2 & I2C_SR2_BUSY){}
    // Genarate start condition
    I2C1->CR1 |= I2C_CR1_START;
    //wait until start flag is set
    while(!(I2C1->SR1 & I2C_SR1_SB)){}
    //transmit slave address + Write //first bit stay 0
    I2C1->DR = saddr << 1;
    //Wait until addr flag is set
    while(!(I2C1->SR1 & I2C_SR1_ADDR)){}
    //clear addr flag, Reading SR2 will clear the add flag
    temp = I2C1->SR2;
    //Wait until transmitter empty
    while(!(I2C1->SR1 & I2C_SR1_TXE)){}
    //Send memory address
    I2C1->DR = maddr;
    for (int i=0; i<n; i++)
    {
        //wait until RXNE is set
        while(!(I2C1->SR1 & I2C_SR1_TXE)){}
        I2C1->DR = *data++;
    }
    while (!(I2C1->SR1 & I2C_SR1_BTF)){}
    //Genarate stop
    I2C1->CR1 |= I2C_CR1_STOP;
}