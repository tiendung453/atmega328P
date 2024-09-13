/*
 * encoder.c
 *
 * Created: 9/12/2024 9:41:03 AM
 *  Author: DungLT
 */ 
#include "steper.h"
void config_encoder()
{
	// Configure motor pins as output
	DDRD |= (1 << MOTOR_PIN1) | (1 << MOTOR_PIN2);
	
	// Configure encoder pins as input with pull-up resistors
	DDRD &= ~((1 << ENCODER_PIN1) | (1 << ENCODER_PIN2));
	PORTD |= (1 << ENCODER_PIN1) | (1 << ENCODER_PIN2);

	// Configure external interrupts for encoder
	EICRA |= (1 << ISC00) | (1 << ISC01); // Trigger on rising edge for INT0
	EICRA |= (1 << ISC10) | (1 << ISC11); // Trigger on rising edge for INT1
	EIMSK |= (1 << INT0) | (1 << INT1);   // Enable interrupts INT0 and INT1

	// Enable global interrupts
	sei();
}

ISR(INT0_vect)
{
	// Handle encoder signal change on INT0
	if (PIND & (1 << ENCODER_PIN1)) 
	{
		encoder_count++;
	} 
	else
	{
		encoder_count--;
	}
}

ISR(INT1_vect) 
{
	// Handle encoder signal change on INT1
	if (PIND & (1 << ENCODER_PIN2)) 
	{
		encoder_count++;
	}
	else 
	{
		encoder_count--;
	}
}