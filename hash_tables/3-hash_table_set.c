#include <stdlib.h>
#include <string.h>
#include "hash_tables.h"

/**
 * hash_table_set - Add/update an element in a hash table
 * @ht: pointer to the hash table
 * @key: key (cannot be empty string)
 * @value: value to store (dup'ed; can be empty string)
 *
 * Return: 1 on success, 0 on error
 */
int hash_table_set(hash_table_t *ht, const char *key, const char *value)
{
	unsigned long int idx;
	hash_node_t *node, *new_node;
	char *vdup;

	if (ht == NULL || key == NULL || *key == '\0' || value == NULL)
		return (0);

	idx = key_index((const unsigned char *)key, ht->size);

	/* Update existing key */
	for (node = ht->array[idx]; node; node = node->next)
	{
		if (strcmp(node->key, key) == 0)
		{
			vdup = strdup(value);
			if (vdup == NULL)
				return (0);
			free(node->value);
			node->value = vdup;
			return (1);
		}
	}

	/* Insert new node at beginning (chaining) */
	new_node = malloc(sizeof(*new_node));
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

	new_node->next = ht->array[idx];
	ht->array[idx] = new_node;

	return (1);
}
