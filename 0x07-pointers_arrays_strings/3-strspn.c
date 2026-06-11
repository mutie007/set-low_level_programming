#include "main.h"

/**
 * _strspn - gets the length of a prefix substring
 * @s: the string to search
 * @accept: the accepted characters
 *
 * Return: number of bytes in s that consist only of bytes from accept
 */
unsigned int _strspn(char *s, char *accept)
{
	unsigned int count;
	int i;
	int found;

	count = 0;
	while (*s != '\0')
	{
		found = 0;
		i = 0;
		while (accept[i] != '\0')
		{
			if (*s == accept[i])
			{
				found = 1;
				break;
			}
			i++;
		}
		if (found == 0)
			break;
		count++;
		s++;
	}
	return (count);
}
