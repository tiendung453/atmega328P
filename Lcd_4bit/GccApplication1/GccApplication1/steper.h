/*
 * encoder.h
 *
 * Created: 9/12/2024 9:41:18 AM
 *  Author: DungLT
 */ 


#ifndef ENCODER_H_
#define ENCODER_H_

#define F_CPU 16000000UL
#include <avr/interrupt.h>
#include "lcd_4bitlib.h"
double controll_speed = 2;

void clock_wise();
void counter_clock_wise();
void increase_speed();
void decrease_speed();
void stop_motor();


#endif /* ENCODER_H_ */