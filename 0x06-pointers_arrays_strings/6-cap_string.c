#include "main.h"

/**
 * cap_string - capitalizes all words of a string
 * @s: pointer to the string
 * Return: pointer to the modified string
 */
char *cap_string(char *s)
{
	int i;
	char sep[] = " \t\n,;.!?\"(){}";
	int j, is_sep;

	i = 0;
	is_sep = 1;
	while (s[i] != '\0')
	{
		j = 0;
		is_sep = 0;
		while (sep[j] != '\0')
		{
			if (s[i] == sep[j])
			{
				is_sep = 1;
				break;
			}
			j++;
		}
		if (is_sep == 0 && i > 0)
		{
			j = 0;
			while (sep[j] != '\0')
			{
				if (s[i - 1] == sep[j])
				{
					if (s[i] >= 'a' && s[i] <= 'z')
						s[i] = s[i] - 32;
					break;
				}
				j++;
			}
		}
		if (i == 0 && s[i] >= 'a' && s[i] <= 'z')
			s[i] = s[i] - 32;
		i++;
	}
	return (s);
}
