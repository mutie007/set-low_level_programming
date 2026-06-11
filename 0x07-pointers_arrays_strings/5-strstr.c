#include "main.h"
#include <stddef.h>

/**
 * _strstr - locates a substring
 * @haystack: the string to search in
 * @needle: the substring to find
 *
 * Return: pointer to beginning of located substring, or NULL if not found
 */
char *_strstr(char *haystack, char *needle)
{
	int i;

	if (*needle == '\0')
		return (haystack);
	while (*haystack != '\0')
	{
		if (*haystack == *needle)
		{
			i = 0;
			while (needle[i] != '\0' && haystack[i] == needle[i])
				i++;
			if (needle[i] == '\0')
				return (haystack);
		}
		haystack++;
	}
	return (NULL);
}
