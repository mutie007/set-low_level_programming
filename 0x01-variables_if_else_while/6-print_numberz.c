#include <stdio.h>

/**
 * main - Entry point, prints all single digit numbers using putchar
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	int n;

	n = 0;
	while (n <= 9)
	{
		putchar('0' + n);
		n++;
	}
	putchar('\n');

	return (0);
}
