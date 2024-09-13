#include "step.h"
int main(void)
{
	DDRD = 0x0F;
	DDRC = 0x00; 
	PORTC = 0xFF;
	uint8_t running = 0;
	uint8_t direction = 0;
	while (PINC == 0xFF);
    while (1)
    {
        switch (PINC) 
		{
	        case 0xFE:
				key_delay();
				clock_wise();
				running = 1;
				direction = 1;
				break;

	        case 0xFD:
				key_delay();
				counter_clock_wise();
				running = 1;
				direction = 0;
				break;

	        case 0xFB:
				key_delay();
				stop_motor();
				running = 0;
				break;

	        case 0xF7:
				key_delay();
				increase_speed();
				if(running)
				{
					if(direction) clock_wise();
					else counter_clock_wise();
				}
				break;

	        case 0xEF:
				key_delay();
				decrease_speed();
				if(running)
				{
					if(direction) clock_wise();
					else counter_clock_wise();
				}
				break;
        }

    }
}
