/*
 * step.h
 *
 * Created: 9/12/2024 9:07:51 PM
 *  Author: DungLT
 */ 


#ifndef STEP_H_
#define STEP_H_

#include "lcd_4bitlib.h"
#include <stdio.h>
#include <stdint.h>
void clock_wise();
void counter_clock_wise();
void increase_speed();
void decrease_speed();
void stop_motor();
void key_delay();
void delay_ms(double d);
void display_step();

#endif /* STEP_H_ */