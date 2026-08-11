#include "hash_tables.h"

/**
 * hash_table_set - adds an element to the hash table
 * @ht: hash table to add/update
 * @key: the key (cannot be empty)
 * @value: the value (will be duplicated)
 *
 * Return: 1 on success, 0 on failure
 */
int hash_table_set(hash_table_t *ht, const char *key, const char *value)
{
	hash_node_t *new, *tmp;
	char *v_copy, *k_copy;
	unsigned long int idx;

	if (!ht || !key || !*key || !value)
		return (0);
	v_copy = strdup(value);
	if (!v_copy)
		return (0);
	idx = key_index((const unsigned char *)key, ht->size);
	tmp = ht->array[idx];
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
	new = malloc(sizeof(hash_node_t));
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
	return (1);
}
