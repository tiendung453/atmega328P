/*
 * keypad.h
 *
 * Created: 9/6/2024 9:30:56 PM
 *  Author: DungLT
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#define  F_CPU 16000000UL
#include <util/delay.h>

#define row_port PORTD
#define row_ddr  DDRD
#define col_pin  PIND
#define col_ddr  DDRD

void key_init();
uint8_t key_scan();


#endif /* KEYPAD_H_ */