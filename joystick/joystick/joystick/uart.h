/*
 * uart.h
 *
 * Created: 10/12/2024 8:04:28 PM
 *  Author: DungLT
 */ 


#ifndef UART_H_
#define UART_H_

#include <avr/io.h>

void UART_Init();
void UART_Transmited(unsigned char data);
void UART_Transmited_Multi_char(unsigned char *data);
unsigned char UART_Received();



#endif /* UART_H_ */