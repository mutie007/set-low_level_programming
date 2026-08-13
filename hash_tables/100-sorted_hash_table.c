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
 * make_shash_node - creates a new sorted hash node
 * @key: the key
 * @value: the value
 *
 * Return: pointer to the new node, or NULL on failure
 */
static shash_node_t *make_shash_node(const char *key, const char *value)
{
	shash_node_t *node;

	node = malloc(sizeof(shash_node_t));
	if (node == NULL)
		return (NULL);

	node->key = strdup(key);
	if (node->key == NULL)
	{
		free(node);
		return (NULL);
	}

	node->value = strdup(value);
	if (node->value == NULL)
	{
		free(node->key);
		free(node);
		return (NULL);
	}

	node->next = NULL;
	node->sprev = NULL;
	node->snext = NULL;

	return (node);
}

/**
 * add_to_sorted_list - inserts a node into the sorted linked list by key
 * @ht: the sorted hash table
 * @node: the node to insert
 */
static void add_to_sorted_list(shash_table_t *ht, shash_node_t *node)
{
	shash_node_t *curr;

	if (ht->shead == NULL)
	{
		ht->shead = node;
		ht->stail = node;
		return;
	}

	curr = ht->shead;
	while (curr != NULL)
	{
		if (strcmp(node->key, curr->key) < 0)
		{
			node->snext = curr;
			node->sprev = curr->sprev;

			if (curr->sprev)
				curr->sprev->snext = node;
			else
				ht->shead = node;

			curr->sprev = node;
			return;
		}
		curr = curr->snext;
	}

	/* insert at the end */
	node->sprev = ht->stail;
	ht->stail->snext = node;
	ht->stail = node;
}

/**
 * shash_table_set - adds or updates an element in a sorted hash table
 * @ht: the sorted hash table
 * @key: the key
 * @value: the value associated with the key
 *
 * Return: 1 on success, 0 on failure
 */
int shash_table_set(shash_table_t *ht, const char *key, const char *value)
{
	unsigned long int index;
	shash_node_t *node, *tmp;
	char *new_value;

	if (ht == NULL || key == NULL || *key == '\0' || value == NULL)
		return (0);

	index = key_index((const unsigned char *)key, ht->size);
	tmp = ht->array[index];

	while (tmp)
	{
		if (strcmp(tmp->key, key) == 0)
		{
			new_value = strdup(value);
			if (new_value == NULL)
				return (0);
			free(tmp->value);
			tmp->value = new_value;
			return (1);
		}
		tmp = tmp->next;
	}

	node = make_shash_node(key, value);
	if (node == NULL)
		return (0);

	node->next = ht->array[index];
	ht->array[index] = node;
	add_to_sorted_list(ht, node);

	return (1);
}

/**
 * shash_table_get - retrieves a value associated with a key
 * @ht: the sorted hash table
 * @key: the key to look for
 *
 * Return: the value associated with the key, or NULL if key not found
 */
char *shash_table_get(const shash_table_t *ht, const char *key)
{
	unsigned long int index;
	shash_node_t *node;

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
 * @ht: the sorted hash table
 */
void shash_table_print(const shash_table_t *ht)
{
	shash_node_t *node;
	char *sep = "";

	if (ht == NULL)
		return;

	printf("{");
	node = ht->shead;
	while (node)
	{
		printf("%s'%s': '%s'", sep, node->key, node->value);
		sep = ", ";
		node = node->snext;
	}
	printf("}\n");
}

/**
 * shash_table_print_rev - prints a sorted hash table in reverse order
 * @ht: the sorted hash table
 */
void shash_table_print_rev(const shash_table_t *ht)
{
	shash_node_t *node;
	char *sep = "";

	if (ht == NULL)
		return;

	printf("{");
	node = ht->stail;
	while (node)
	{
		printf("%s'%s': '%s'", sep, node->key, node->value);
		sep = ", ";
		node = node->sprev;
	}
	printf("}\n");
}

/**
 * shash_table_delete - deletes a sorted hash table
 * @ht: the sorted hash table
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
