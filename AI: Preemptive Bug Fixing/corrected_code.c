#include <stdlib.h>

/**
 * struct list_s - singly linked list
 * @n: integer
 * @next: points to the next node
 *
 * Description: singly linked list node structure
 */
typedef struct list_s
{
	int n;
	struct list_s *next;
} list_t;

/**
 * add_node_end - Adds a new node at the end of a list_t list (CORRECTED VERSION)
 * @head: Pointer to the head of the list
 * @n: Integer to be added in the new node
 *
 * Return: Address of the new element, or NULL if it failed
 */
list_t *add_node_end(list_t *head, const int n)
{
	list_t *new_node = malloc(sizeof(list_t));
	list_t *current;

	/* Memory safety: check if malloc succeeded */
	if (new_node == NULL)
		return (NULL);

	new_node->n = n;
	new_node->next = NULL;

	/* Empty list case */
	if (head == NULL)
		return (new_node);

	/* Traverse to the last node (stop before NULL) */
	current = head;
	while (current->next != NULL)
		current = current->next;

	/* Correctly link the new node */
	current->next = new_node;

	return (head);
}
