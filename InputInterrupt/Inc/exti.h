/*
 * exti.h
 *
 *  Created on: Apr 5, 2024
 *      Author: Oussema Raissi
 */

#ifndef EXTI_H_
#define EXTI_H_
#include "stm32f401xc.h"
#define LINE4   (1U << 4)
void pa4_exti_init(void);
#endif /* EXTI_H_ */
