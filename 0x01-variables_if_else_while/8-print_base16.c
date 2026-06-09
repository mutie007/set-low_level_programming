#include <stdio.h>

/**
 * main - Entry point, prints all numbers of base 16 in lowercase
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	int n;
	char c;

	n = 0;
	while (n <= 9)
	{
		putchar('0' + n);
		n++;
	}
	c = 'a';
	while (c <= 'f')
	{
		putchar(c);
		c++;
	}
	putchar('\n');

	return (0);
}
