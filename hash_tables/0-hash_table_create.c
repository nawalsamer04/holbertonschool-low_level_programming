#include "hash_tables.h"

/**
 * hash_table_create - Create a new hash table
 * @size: size of the array
 *
 * Return: pointer to the new hash table, or NULL on failure
 */
hash_table_t *hash_table_create(unsigned long int size)
{
	hash_table_t *ht;

	if (size == 0)
		return (NULL);

	ht = malloc(sizeof(hash_table_t));
	if (ht == NULL)
		return (NULL);

	ht->size = size;
	/* calloc zeroes the bucket pointers (NULL) */
	ht->array = calloc(size, sizeof(hash_node_t *));
	if (ht->array == NULL)
	{
		free(ht);
		return (NULL);
	}

	return (ht);
}
