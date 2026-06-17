#include <stdio.h>

/**
 * main - adds positive numbers passed as arguments
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: 0 on success, 1 if a non-digit argument is found
 */
int main(int argc, char *argv[])
{
	int i;
	int j;
	int sum;
	int num;

	sum = 0;
	i = 1;
	while (i < argc)
	{
		num = 0;
		j = 0;
		while (argv[i][j] != '\0')
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
			{
				printf("Error\n");
				return (1);
			}
			num = num * 10 + (argv[i][j] - '0');
			j++;
		}
		sum += num;
		i++;
	}
	printf("%d\n", sum);
	return (0);
}
