#include "main.h"

/**
 * print_line - draws a straight line in the terminal
 * @n: number of times to print '_'
 */
void print_line(int n)
{
	int i;

	i = 0;
	while (i < n)
	{
		_putchar('_');
		i++;
	}
	_putchar('\n');
}
