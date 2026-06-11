#include "main.h"

/**
 * sqrt_helper - helper function to find square root recursively
 * @n: the number to find square root of
 * @i: current guess
 * Return: square root if found, -1 otherwise
 */
int sqrt_helper(int n, int i)
{
	if (i * i > n)
		return (-1);
	if (i * i == n)
		return (i);
	return (sqrt_helper(n, i + 1));
}

/**
 * _sqrt_recursion - returns the natural square root of a number
 * @n: the number to find square root of
 * Return: natural square root of n, or -1 if no natural square root
 */
int _sqrt_recursion(int n)
{
	if (n < 0)
		return (-1);
	return (sqrt_helper(n, 0));
}
