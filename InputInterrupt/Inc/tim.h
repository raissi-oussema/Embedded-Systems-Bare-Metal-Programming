/*
 * tim.h
 *
 *  Created on: Mar 31, 2024
 *      Author: Oussema Raissi
 */

#ifndef TIM_H_
#define TIM_H_
#define MAX_INT_DIGITS 11 // Maximum digits in a signed 32-bit integer (+ 1 for null terminator)
void tim2_1hz_init(void);
void tim2_pa5_compare_mode(void);
void tim3_pin6_input_capture(void);
char* convertToString(int num, char* str);
#endif /* TIM_H_ */
