#include "hash_tables.h"

/**
 * shash_table_create - creates a sorted hash table
 * @size: size of the array
 *
 * Return: pointer to the new sorted hash table, or NULL on failure
 */
shash_table_t *shash_table_create(unsigned long int size)
{
	shash_table_t *ht;
	unsigned long int i;

	ht = malloc(sizeof(shash_table_t));
	if (ht == NULL)
		return (NULL);

	ht->size = size;
	ht->shead = NULL;
	ht->stail = NULL;
	ht->array = malloc(sizeof(shash_node_t *) * size);
	if (ht->array == NULL)
	{
		free(ht);
		return (NULL);
	}

	for (i = 0; i < size; i++)
		ht->array[i] = NULL;

	return (ht);
}

/**
 * shash_table_set - adds an element to the sorted hash table
 * @ht: sorted hash table
 * @key: the key
 * @value: the value associated with the key
 *
 * Return: 1 on success, 0 on failure
 */
int shash_table_set(shash_table_t *ht, const char *key, const char *value)
{
	shash_node_t *node, *tmp;
	char *value_copy;
	unsigned long int index;

	if (ht == NULL || key == NULL || *key == '\0' || value == NULL)
		return (0);

	value_copy = strdup(value);
	if (value_copy == NULL)
		return (0);

	index = key_index((const unsigned char *)key, ht->size);
	tmp = ht->array[index];

	/* Check if key already exists → update value only */
	while (tmp)
	{
		if (strcmp(tmp->key, key) == 0)
		{
			free(tmp->value);
			tmp->value = value_copy;
			return (1);
		}
		tmp = tmp->next;
	}

	/* Create new node */
	node = malloc(sizeof(shash_node_t));
	if (node == NULL)
	{
		free(value_copy);
		return (0);
	}
	node->key = strdup(key);
	if (node->key == NULL)
	{
		free(value_copy);
		free(node);
		return (0);
	}
	node->value = value_copy;
	node->next = ht->array[index];
	ht->array[index] = node;

	/* Insert into sorted doubly linked list (by key ASCII order) */
	if (ht->shead == NULL)
	{
		node->sprev = NULL;
		node->snext = NULL;
		ht->shead = node;
		ht->stail = node;
		return (1);
	}

	if (strcmp(ht->shead->key, key) > 0)
	{
		/* Insert at the beginning */
		node->sprev = NULL;
		node->snext = ht->shead;
		ht->shead->sprev = node;
		ht->shead = node;
		return (1);
	}

	tmp = ht->shead;
	while (tmp->snext && strcmp(tmp->snext->key, key) < 0)
		tmp = tmp->snext;

	node->sprev = tmp;
	node->snext = tmp->snext;

	if (tmp->snext)
		tmp->snext->sprev = node;
	else
		ht->stail = node;

	tmp->snext = node;

	return (1);
}

/**
 * shash_table_get - retrieves a value associated with a key
 * @ht: sorted hash table
 * @key: the key
 *
 * Return: value associated with the key, or NULL if not found
 */
char *shash_table_get(const shash_table_t *ht, const char *key)
{
	shash_node_t *node;
	unsigned long int index;

	if (ht == NULL || key == NULL || *key == '\0')
		return (NULL);

	index = key_index((const unsigned char *)key, ht->size);
	node = ht->array[index];

	while (node)
	{
		if (strcmp(node->key, key) == 0)
			return (node->value);
		node = node->next;
	}
	return (NULL);
}

/**
 * shash_table_print - prints a sorted hash table
 * @ht: sorted hash table
 */
void shash_table_print(const shash_table_t *ht)
{
	shash_node_t *node;
	int comma = 0;

	if (ht == NULL)
		return;

	printf("{");
	node = ht->shead;
	while (node)
	{
		if (comma)
			printf(", ");
		printf("'%s': '%s'", node->key, node->value);
		comma = 1;
		node = node->snext;
	}
	printf("}\n");
}

/**
 * shash_table_print_rev - prints a sorted hash table in reverse order
 * @ht: sorted hash table
 */
void shash_table_print_rev(const shash_table_t *ht)
{
	shash_node_t *node;
	int comma = 0;

	if (ht == NULL)
		return;

	printf("{");
	node = ht->stail;
	while (node)
	{
		if (comma)
			printf(", ");
		printf("'%s': '%s'", node->key, node->value);
		comma = 1;
		node = node->sprev;
	}
	printf("}\n");
}

/**
 * shash_table_delete - deletes a sorted hash table
 * @ht: sorted hash table
 */
void shash_table_delete(shash_table_t *ht)
{
	shash_node_t *node, *tmp;

	if (ht == NULL)
		return;

	node = ht->shead;
	while (node)
	{
		tmp = node->snext;
		free(node->key);
		free(node->value);
		free(node);
		node = tmp;
	}

	free(ht->array);
	free(ht);
}
