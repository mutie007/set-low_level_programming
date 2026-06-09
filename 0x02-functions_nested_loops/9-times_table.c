#include "main.h"

/**
 * times_table - prints the 9 times table starting with 0
 */
void times_table(void)
{
	int i, j, product;

	for (i = 0; i <= 9; i++)
	{
		for (j = 0; j <= 9; j++)
		{
			product = i * j;

			if (j == 0)
			{
				_putchar('0');
			}
			else
			{
				_putchar(',');
				if (product >= 10)
					_putchar(' ');
				else
					_putchar(' '), _putchar(' ');

				if (product == 0)
					_putchar('0');
				else
				{
					if (product >= 10)
						_putchar('0' + product / 10);
					_putchar('0' + product % 10);
				}
			}
		}
		_putchar('\n');
	}
}
