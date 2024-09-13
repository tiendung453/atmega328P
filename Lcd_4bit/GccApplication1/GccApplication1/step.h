/*
 * step.h
 *
 * Created: 9/12/2024 9:07:51 PM
 *  Author: DungLT
 */ 


#ifndef STEP_H_
#define STEP_H_

#define F_CPU 16000000UL
#include "lcd_4bitlib.h"

void clock_wise();
void counter_clock_wise();
void increase_speed();
void decrease_speed();
void stop_motor();
void key_delay();
void delay_ms(double d);


#endif /* STEP_H_ */