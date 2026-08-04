#include "lists.h"

/**
 * sum_listint - returns the sum of all data in a listint_t linked list
 * @head: pointer to the head of the list
 *
 * Return: sum of all n values, or 0 if list is empty
 */
int sum_listint(listint_t *head)
{
	int sum;

	sum = 0;
	while (head != NULL)
	{
		sum += head->n;
		head = head->next;
	}
	return (sum);
}
