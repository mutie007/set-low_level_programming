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
	size_t i;
	const listint_t *slow;
	const listint_t *fast;

	count = 0;
	slow = head;
	fast = head;
	while (fast != NULL && fast->next != NULL)
	{
		slow = slow->next;
		fast = fast->next->next;
		count++;
		if (slow == fast)
		{
			slow = head;
			i = 0;
			while (slow != fast)
			{
				slow = slow->next;
				fast = fast->next;
				i++;
			}
			count = i;
			slow = head;
			while (i > 0)
			{
				printf("[%p] %d\n", (void *)slow, slow->n);
				slow = slow->next;
				i--;
			}
			printf("-> [%p] %d\n", (void *)slow, slow->n);
			exit(98);
		}
	}
	count = 0;
	while (head != NULL)
	{
		printf("[%p] %d\n", (void *)head, head->n);
		head = head->next;
		count++;
	}
	return (count);
}
