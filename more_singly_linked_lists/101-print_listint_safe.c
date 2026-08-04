#include "lists.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * print_listint_safe - prints a listint_t linked list (safe version)
 * @head: pointer to the head of the list
 *
 * Return: the number of nodes in the list
 */
size_t print_listint_safe(const listint_t *head)
{
	const listint_t *current;
	const listint_t **addrs;
	size_t i, count = 0;
	size_t size = 10;

	addrs = malloc(sizeof(listint_t *) * size);
	if (addrs == NULL)
		exit(98);

	current = head;
	while (current != NULL)
	{
		for (i = 0; i < count; i++)
		{
			if (current == addrs[i])
			{
				printf("-> [%p] %d\n", (void *)current, current->n);
				free(addrs);
				return (count);
			}
		}

		if (count == size)
		{
			size *= 2;
			addrs = realloc(addrs, sizeof(listint_t *) * size);
			if (addrs == NULL)
				exit(98);
		}

		addrs[count] = current;
		printf("[%p] %d\n", (void *)current, current->n);
		count++;
		current = current->next;
	}

	free(addrs);
	return (count);
}
