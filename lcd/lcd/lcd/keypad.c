/*
 * keypad.c
 *
 * Created: 9/6/2024 9:31:11 PM
 *  Author: DungLT
 */ 
#include "keypad.h"
void key_init()
{
	row_ddr = 0x0F;
	row_port = 0xFF;
	
	col_ddr = 0x0F;
	
}
unsigned char key_scan()
{
	uint8_t row = 1, input;
	for(row = 1; row <= 4; row++)
	{

		row_port |= 0x0F;
		row_port &= ~(1 << (row - 1));
		input = col_pin & 0xF0; 
		switch(row)
		{
			case 1:
				switch(input)
				{
					case 0xE0: 
						return 0x07;
						break;
					case 0xD0: 
						return 0x08;
						break;
					case 0xB0: 
						return 0x09;
						break;
					case 0x70: 
						return 0x0A;
						break;
				}
				break;
			case 2:
				switch(input)
				{
					case 0xE0: 
						return 0x04;
						break;
					case 0xD0: 
						return 0x05;
						break;
					case 0xB0: 
						return 0x06;
						break;
					case 0x70: 
						return 0x0B;
						break;
				}
				break;
			case 3:
				switch(input)
				{
					case 0xE0: 
						return 0x01;
						break;
					case 0xD0: 
						return 0x02;
						break;
					case 0xB0: 
						return 0x03;
						break;
					case 0x70: 
						return 0x0C;
						break;
				}
				break;
			case 4:
				switch(input)
				{
					case 0xE0: 
						return 0x0F;
						break;
					case 0xD0: 
						return '0';
						break;
					case 0xB0: 
						return 0X0E;
						break;
					case 0x70: 
						return 0X0D;
						break;
						
					
				}
				break;
		}		
	}
	return 0;
}
