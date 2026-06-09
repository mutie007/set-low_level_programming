#include "main.h"

/**
 * print_last_digit - prints the last digit of a number
 * @n: the number to print last digit of
 *
 * Return: the value of the last digit
 */
int print_last_digit(int n)
{
	int last;

	last = n % 10;
	if (last < 0)
		last = -last;
	_putchar('0' + last);
	return (last);
}
