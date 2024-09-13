#include "lcd.h"
#include <stdio.h>
#include <stdint.h>

int main(void) {
	lcd_init();
	key_init();
	lcd_gotoxy(1, 2);

	while (1)
	{
		calculator();
		_delay_us(10000);
	}

	return 0;
}
