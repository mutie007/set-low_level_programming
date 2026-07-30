#include <stdlib.h>
#include "lists.h"

/**
 * free_listint2 - frees a listint_t list and sets head to NULL
 * @head: pointer to the pointer of the head of the list
 *
 * Return: void
 */
void free_listint2(listint_t **head)
{
	listint_t *tmp;

	while (*head != NULL)
	{
		tmp = (*head)->next;
		free(*head);
		*head = tmp;
	}
	*head = NULL;
}
