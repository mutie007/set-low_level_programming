#include <stdlib.h>
#include "lists.h"

/**
 * delete_nodeint_at_index - deletes the node at index of a listint_t list
 * @head: pointer to the pointer of the head of the list
 * @index: index of the node to delete
 *
 * Return: 1 if succeeded, -1 if failed
 */
int delete_nodeint_at_index(listint_t **head, unsigned int index)
{
	listint_t *tmp;
	listint_t *prev;
	unsigned int i;

	if (*head == NULL)
		return (-1);

	if (index == 0)
	{
		tmp = *head;
		*head = (*head)->next;
		free(tmp);
		return (1);
	}

	prev = *head;
	for (i = 0; i < index - 1; i++)
	{
		if (prev->next == NULL)
			return (-1);
		prev = prev->next;
	}

	if (prev->next == NULL)
		return (-1);

	tmp = prev->next;
	prev->next = tmp->next;
	free(tmp);

	return (1);
}
