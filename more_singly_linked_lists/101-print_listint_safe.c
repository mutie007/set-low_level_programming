#include <stdio.h>
#include <stdlib.h>
#include "lists.h"

/**
 * is_looped - checks if a node was already visited
 * @visited: array of visited node pointers
 * @count: number of visited nodes
 * @node: node to check
 *
 * Return: 1 if looped, 0 otherwise
 */
static int is_looped(const listint_t **visited, size_t count,
		const listint_t *node)
{
	size_t i;

	i = 0;
	while (i < count)
	{
		if (visited[i] == node)
			return (1);
		i++;
	}
	return (0);
}

/**
 * print_listint_safe - prints a listint_t linked list safely
 * @head: pointer to head of list
 *
 * Return: number of nodes in the list
 */
size_t print_listint_safe(const listint_t *head)
{
	const listint_t **visited;
	const listint_t *current;
	size_t count;
	size_t size;

	if (head == NULL)
		return (0);
	size = 1024;
	visited = malloc(sizeof(listint_t *) * size);
	if (visited == NULL)
		exit(98);
	count = 0;
	current = head;
	while (current != NULL)
	{
		if (is_looped(visited, count, current))
		{
			printf("-> [%p] %d\n", (void *)current, current->n);
			free(visited);
			exit(98);
		}
		if (count >= size)
		{
			size *= 2;
			visited = realloc(visited, sizeof(listint_t *) * size);
			if (visited == NULL)
				exit(98);
		}
		visited[count] = current;
		printf("[%p] %d\n", (void *)current, current->n);
		count++;
		current = current->next;
	}
	free(visited);
	return (count);
}
