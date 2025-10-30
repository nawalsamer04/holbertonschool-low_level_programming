#include <string.h>
#include "hash_tables.h"

/**
 * hash_table_get - Retrieve the value associated with a key
 * @ht:  pointer to the hash table
 * @key: key to look for (must be non-NULL and non-empty)
 *
 * Return: pointer to the value if found, otherwise NULL
 */
char *hash_table_get(const hash_table_t *ht, const char *key)
{
	unsigned long int idx;
	hash_node_t *node;

	if (ht == NULL || key == NULL || *key == '\0')
		return (NULL);

	idx = key_index((const unsigned char *)key, ht->size);
	node = ht->array[idx];

	while (node)
	{
		if (strcmp(node->key, key) == 0)
			return (node->value); /* value was strdup’ed by set */
		node = node->next;
	}
	return (NULL);
}
