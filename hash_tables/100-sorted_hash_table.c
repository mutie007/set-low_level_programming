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
	ht->array = malloc(sizeof(shash_node_t *) * size);
	if (ht->array == NULL)
	{
		free(ht);
		return (NULL);
	}

	for (i = 0; i < size; i++)
		ht->array[i] = NULL;

	ht->shead = NULL;
	ht->stail = NULL;

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
	shash_node_t *new, *tmp;
	char *v_copy, *k_copy;
	unsigned long int idx;

	if (!ht || !key || !*key || !value)
		return (0);

	v_copy = strdup(value);
	if (!v_copy)
		return (0);

	idx = key_index((const unsigned char *)key, ht->size);
	tmp = ht->array[idx];

	/* Update if key already exists */
	while (tmp)
	{
		if (strcmp(tmp->key, key) == 0)
		{
			free(tmp->value);
			tmp->value = v_copy;
			return (1);
		}
		tmp = tmp->next;
	}

	/* Create new node */
	new = malloc(sizeof(shash_node_t));
	if (!new)
	{
		free(v_copy);
		return (0);
	}
	k_copy = strdup(key);
	if (!k_copy)
	{
		free(v_copy);
		free(new);
		return (0);
	}

	new->key = k_copy;
	new->value = v_copy;
	new->next = ht->array[idx];
	ht->array[idx] = new;

	/* Insert into sorted linked list */
	if (ht->shead == NULL)
	{
		new->sprev = NULL;
		new->snext = NULL;
		ht->shead = new;
		ht->stail = new;
		return (1);
	}

	tmp = ht->shead;
	while (tmp && strcmp(tmp->key, key) < 0)
		tmp = tmp->snext;

	if (tmp == ht->shead) /* insert at beginning */
	{
		new->sprev = NULL;
		new->snext = ht->shead;
		ht->shead->sprev = new;
		ht->shead = new;
	}
	else if (tmp == NULL) /* insert at end */
	{
		new->sprev = ht->stail;
		new->snext = NULL;
		ht->stail->snext = new;
		ht->stail = new;
	}
	else /* insert in the middle */
	{
		new->sprev = tmp->sprev;
		new->snext = tmp;
		tmp->sprev->snext = new;
		tmp->sprev = new;
	}

	return (1);
}

/**
 * shash_table_get - retrieves a value associated with a key
 * @ht: sorted hash table
 * @key: the key
 *
 * Return: the value, or NULL if not found
 */
char *shash_table_get(const shash_table_t *ht, const char *key)
{
	shash_node_t *node;
	unsigned long int idx;

	if (!ht || !key || !*key)
		return (NULL);

	idx = key_index((const unsigned char *)key, ht->size);
	node = ht->array[idx];

	while (node)
	{
		if (strcmp(node->key, key) == 0)
			return (node->value);
		node = node->next;
	}
	return (NULL);
}

/**
 * shash_table_print - prints the sorted hash table
 * @ht: sorted hash table
 */
void shash_table_print(const shash_table_t *ht)
{
	shash_node_t *node;
	int first = 1;

	if (!ht)
		return;

	printf("{");
	node = ht->shead;
	while (node)
	{
		if (!first)
			printf(", ");
		printf("'%s': '%s'", node->key, node->value);
		first = 0;
		node = node->snext;
	}
	printf("}\n");
}

/**
 * shash_table_print_rev - prints the sorted hash table in reverse
 * @ht: sorted hash table
 */
void shash_table_print_rev(const shash_table_t *ht)
{
	shash_node_t *node;
	int first = 1;

	if (!ht)
		return;

	printf("{");
	node = ht->stail;
	while (node)
	{
		if (!first)
			printf(", ");
		printf("'%s': '%s'", node->key, node->value);
		first = 0;
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
	shash_node_t *node, *temp;

	if (!ht)
		return;

	node = ht->shead;
	while (node)
	{
		temp = node->snext;
		free(node->key);
		free(node->value);
		free(node);
		node = temp;
	}
	free(ht->array);
	free(ht);
}
