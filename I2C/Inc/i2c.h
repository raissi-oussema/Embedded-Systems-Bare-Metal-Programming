#ifndef _I2C_H
#define _I2C_H
#include "stm32f401xc.h"

void I2C1_init(void);
void I2C1_byteRead(char saddr, char maddr, char *data);
void I2C1_burstRead(char saddr, char maddr, int n, char *data);
void I2C1_burstWrite(char saddr, char maddr, int n, char *data);

#endif 
