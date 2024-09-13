#include <avr/io.h>
#include"config.h"
#include <util/delay.h>
#include <stdint.h>


int main(void)
{

	 DDRD = 0xFF;

	uint8_t run = 2;  

	while (1)
	{
		PORTD = run; 
	}
}
