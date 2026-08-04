#include "lists.h"
#include <stdlib.h>

/**
 * free_listint_safe - frees a listint_t list (safe version)
 * @h: pointer to the pointer of the head of the list
 *
 * Return: the size of the list that was free'd
 */
size_t free_listint_safe(listint_t **h)
{
	listint_t *current, *tmp;
	listint_t **addrs;
	size_t i, count = 0;
	size_t size = 10;

	if (h == NULL || *h == NULL)
		return (0);

	addrs = malloc(sizeof(listint_t *) * size);
	if (addrs == NULL)
		exit(98);

	current = *h;
	while (current != NULL)
	{
		for (i = 0; i < count; i++)
		{
			if (current == addrs[i])
			{
				*h = NULL;
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
		tmp = current->next;
		free(current);
		current = tmp;
		count++;
	}

	*h = NULL;
	free(addrs);
	return (count);
}
