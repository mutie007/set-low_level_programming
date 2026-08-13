#include "hash_tables.h"

/**
 * shash_table_create - creates a sorted hash table
 * @size: size of the array
 *
 * Return: pointer to the new hash table, or NULL on failure
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
 * shash_table_set - adds or updates a key/value pair in the sorted hash table
 * @ht: pointer to the hash table
 * @key: the key string
 * @value: the value string
 *
 * Return: 1 on success, 0 on failure
 */
int shash_table_set(shash_table_t *ht, const char *key, const char *value)
{
	shash_node_t *new_node;
	shash_node_t *tmp;
	unsigned long int index;

	if (ht == NULL || key == NULL || *key == '\0')
		return (0);

	index = key_index((const unsigned char *)key, ht->size);

	tmp = ht->array[index];
	while (tmp != NULL)
	{
		if (strcmp(tmp->key, key) == 0)
		{
			free(tmp->value);
			tmp->value = strdup(value);
			return (tmp->value != NULL ? 1 : 0);
		}
		tmp = tmp->next;
	}

	new_node = malloc(sizeof(shash_node_t));
	if (new_node == NULL)
		return (0);

	new_node->key = strdup(key);
	if (new_node->key == NULL)
	{
		free(new_node);
		return (0);
	}

	new_node->value = strdup(value);
	if (new_node->value == NULL)
	{
		free(new_node->key);
		free(new_node);
		return (0);
	}

	new_node->next = ht->array[index];
	ht->array[index] = new_node;

	new_node->sprev = NULL;
	new_node->snext = NULL;

	if (ht->shead == NULL)
	{
		ht->shead = new_node;
		ht->stail = new_node;
		return (1);
	}

	tmp = ht->shead;
	while (tmp != NULL && strcmp(tmp->key, key) < 0)
		tmp = tmp->snext;

	if (tmp == ht->shead)
	{
		new_node->snext = ht->shead;
		ht->shead->sprev = new_node;
		ht->shead = new_node;
	}
	else if (tmp == NULL)
	{
		new_node->sprev = ht->stail;
		ht->stail->snext = new_node;
		ht->stail = new_node;
	}
	else
	{
		new_node->snext = tmp;
		new_node->sprev = tmp->sprev;
		tmp->sprev->snext = new_node;
		tmp->sprev = new_node;
	}

	return (1);
}

/**
 * shash_table_get - retrieves a value associated with a key
 * @ht: pointer to the hash table
 * @key: the key string
 *
 * Return: the value, or NULL if key not found
 */
char *shash_table_get(const shash_table_t *ht, const char *key)
{
	shash_node_t *tmp;
	unsigned long int index;

	if (ht == NULL || key == NULL || *key == '\0')
		return (NULL);

	index = key_index((const unsigned char *)key, ht->size);
	tmp = ht->array[index];

	while (tmp != NULL)
	{
		if (strcmp(tmp->key, key) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

/**
 * shash_table_print - prints the hash table using the sorted linked list
 * @ht: pointer to the hash table
 */
void shash_table_print(const shash_table_t *ht)
{
	shash_node_t *tmp;

	if (ht == NULL)
		return;

	printf("{");
	tmp = ht->shead;
	while (tmp != NULL)
	{
		printf("'%s': '%s'", tmp->key, tmp->value);
		if (tmp->snext != NULL)
			printf(", ");
		tmp = tmp->snext;
	}
	printf("}\n");
}

/**
 * shash_table_print_rev - prints the hash table in reverse order
 * @ht: pointer to the hash table
 */
void shash_table_print_rev(const shash_table_t *ht)
{
	shash_node_t *tmp;

	if (ht == NULL)
		return;

	printf("{");
	tmp = ht->stail;
	while (tmp != NULL)
	{
		printf("'%s': '%s'", tmp->key, tmp->value);
		if (tmp->sprev != NULL)
			printf(", ");
		tmp = tmp->sprev;
	}
	printf("}\n");
}

/**
 * shash_table_delete - deletes a sorted hash table
 * @ht: pointer to the hash table
 */
void shash_table_delete(shash_table_t *ht)
{
	shash_node_t *tmp;
	shash_node_t *next;

	if (ht == NULL)
		return;

	tmp = ht->shead;
	while (tmp != NULL)
	{
		next = tmp->snext;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
		tmp = next;
	}

	free(ht->array);
	free(ht);
}
