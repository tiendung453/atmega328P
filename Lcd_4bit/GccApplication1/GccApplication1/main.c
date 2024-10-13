#include "tick.h"
int main(void)
{
	DDRD = 0xFF;
	DDRC = 0x00;
	PORTC = 0xFF;
	pcint_init();
	lcd_init();
	lcd_print("Dung's Project!");

	while (PINC == 0x7F);
	while (1)
	{
		display_step();
		select_mode();
		display_mode();
	}
}