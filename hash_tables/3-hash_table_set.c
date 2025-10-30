#include "hash_tables.h"

/* small internal strdup to avoid portability issues */
static char *dupstr(const char *s)
{
	size_t len;
	char *p;

	if (!s)
		return (NULL);
	len = strlen(s) + 1;
	p = malloc(len);
	if (!p)
		return (NULL);
	memcpy(p, s, len);
	return (p);
}

/**
 * hash_table_set - add/update a key/value in the hash table
 * @ht:   hash table
 * @key:  key (non-empty)
 * @value:value (duplicated; can be empty string but not NULL)
 *
 * Return: 1 on success, 0 on error
 */
int hash_table_set(hash_table_t *ht, const char *key, const char *value)
{
	unsigned long int idx;
	hash_node_t *node, *head;

	if (!ht || !ht->array || !key || *key == '\0' || !value)
		return (0);

	idx = key_index((const unsigned char *)key, ht->size);
	/* update if key already exists */
	for (node = ht->array[idx]; node; node = node->next)
	{
		if (strcmp(node->key, key) == 0)
		{
			char *nv = dupstr(value);

			if (!nv)
				return (0);
			free(node->value);
			node->value = nv;
			return (1);
		}
	}

	/* insert at beginning (collision handling by chaining) */
	node = malloc(sizeof(*node));
	if (!node)
		return (0);
	node->key = dupstr(key);
	node->value = dupstr(value);
	if (!node->key || !node->value)
	{
		free(node->key);
		free(node->value);
		free(node);
		return (0);
	}
	head = ht->array[idx];
	node->next = head;
	ht->array[idx] = node;
	return (1);
}
