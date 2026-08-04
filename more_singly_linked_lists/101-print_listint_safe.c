#include <stdio.h>
#include <stdlib.h>
#include "lists.h"

/**
 * print_listint_safe - prints a listint_t linked list safely
 * @head: pointer to head of list
 *
 * Return: number of nodes in the list
 */
size_t print_listint_safe(const listint_t *head)
{
	size_t count;
	size_t loop_pos;
	const listint_t *slow;
	const listint_t *fast;
	const listint_t *start;

	if (head == NULL)
		return (0);
	slow = head;
	fast = head;
	while (fast != NULL && fast->next != NULL)
	{
		slow = slow->next;
		fast = fast->next->next;
		if (slow == fast)
		{
			start = head;
			loop_pos = 0;
			while (start != slow)
			{
				start = start->next;
				slow = slow->next;
				loop_pos++;
			}
			count = 0;
			start = head;
			while (count < loop_pos)
			{
				printf("[%p] %d\n", (void *)start, start->n);
				start = start->next;
				count++;
			}
			printf("-> [%p] %d\n", (void *)start, start->n);
			exit(98);
		}
	}
	count = 0;
	start = head;
	while (start != NULL)
	{
		printf("[%p] %d\n", (void *)start, start->n);
		start = start->next;
		count++;
	}
	return (count);
}
