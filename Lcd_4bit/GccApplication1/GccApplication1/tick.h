/*
 * tick.h
 *
 * Created: 9/17/2024 3:55:03 PM
 *  Author: DungLT
 */ 


#ifndef TICK_H_
#define TICK_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include "step.h"

void timer1_init(void);
ISR(TIMER1_COMPA_vect);
uint32_t GetTick(void);

void pcint_init(void);
ISR(PCINT1_vect);

void select_mode();
void display_mode();

#endif /* TICK_H_ */