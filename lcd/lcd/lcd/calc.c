#include "calc.h"
long int a = 0;
long int b = 0;
static uint8_t option = 0;
static float result;
int whole_part;
int decimal_part;

uint8_t key;
static char op_char;
static char lcd_buff[20];
static char lcd_buff1[20];

void cal_op()
{
	switch (key)
	{
		case 0x0D:
			op_char = '+';
			option = 1;
			key =0;
		    break;
		case 0x0C:
			op_char = '-';
			option = 2;
			key =0;
			break;
		case 0x0B:
			op_char = 'x';
			option = 3;
			key =0;
			break;
		case 0x0A:
			op_char = '/';
			option = 4;
			key =0;
			break;
		case 0x0E:
			option = 5;
			break;
		case 0x0F:
			option = 0;
			a = 0;
			b = 0;
			result = 0;
			key = 0;
			lcdCommand(0x01);
			break;
		case '0':
			key = 0;
			break;
	}
}

void calculate()
{
	cal_op();
	if (option == 0)
	{
			
			a = a * 10 + key;
			if(a == 0)
			{
				lcdCommand(0x01);
			}
			sprintf(lcd_buff, "%ld", a);
			lcd_gotoxy(1,1);
			lcd_print(lcd_buff);
		
	}
	else if (option == 1 || option == 2|| option == 3|| option == 4)
	{
			b = b * 10 + key,
			sprintf(lcd_buff, "%ld%c%ld", a, op_char, b);
			lcd_gotoxy(1,1);
			lcd_print(lcd_buff);
	}
	else if (option == 5)
	{
		lcd_gotoxy(1,2);
		lcd_print("                         ");
		switch (op_char)
		{
			case '+':
				result = a+b;
				whole_part = (int)result;
			    decimal_part = (int)((result - whole_part) * 1000);
				break;
			case '-':
				result = a-b;
				whole_part = (int)result;
				decimal_part = (int)((result - whole_part) * 1000);
				break;
			case 'x':
				result =a*b;
				whole_part = (int)result;
				decimal_part = (int)((result - whole_part) * 1000); 
				break;
			case '/':
				if (b != 0)
				{
					if(a%2 == 0)
					{
						result = (double)a / b;
						whole_part = (int)result;
						decimal_part = (int)((result - whole_part) * 1000);
					}	
					else
					{
						result = (double)a / b;
						whole_part = (int)result;
						decimal_part = (int)((result - whole_part) * 100 + 1);	
					}
				}
				else
				{
					lcd_gotoxy(1,2);
					lcd_print("Error"); 
				}
				break;
		}
		if (op_char == '/' && b == 0)
		{
					lcd_gotoxy(1,2);
					lcd_print("Error");

		}
		else
		{
						sprintf(lcd_buff1, "%d.%02d", whole_part, decimal_part);
						lcd_gotoxy(1,2);
						lcd_print(lcd_buff1);
						
						a = 0;
						b = 0;
						result = 0;
						option = 0;
		}
	}
}

void calculator(void)
{
	key = key_scan();
	if(key != 0)
	{
		calculate();
		key = 0;
	}
}
