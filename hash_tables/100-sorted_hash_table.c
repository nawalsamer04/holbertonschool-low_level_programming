#include "hash_tables.h"

/**
 * shash_table_create - Creates a sorted hash table
 * @size: size of the array
 *
 * Return: pointer to new table or NULL
 */
shash_table_t *shash_table_create(unsigned long int size)
{
	shash_table_t *ht;
	unsigned long int i;

	if (size == 0)
		return (NULL);

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
 * shash_table_set - Adds or updates an element in a sorted hash table
 * @ht: pointer to the sorted hash table
 * @key: key string (non-empty)
 * @value: value string (duplicated)
 *
 * Return: 1 on success, 0 on failure
 */
int shash_table_set(shash_table_t *ht, const char *key, const char *value)
{
	unsigned long int index;
	shash_node_t *node, *new, *curr;
	char *val_copy;

	if (ht == NULL || key == NULL || *key == '\0' || value == NULL)
		return (0);

	index = key_index((const unsigned char *)key, ht->size);

	/* update if key already exists in bucket */
	for (node = ht->array[index]; node; node = node->next)
	{
		if (strcmp(node->key, key) == 0)
		{
			val_copy = strdup(value);
			if (val_copy == NULL)
				return (0);
			free(node->value);
			node->value = val_copy;
			return (1);
		}
	}

	/* new node */
	new = malloc(sizeof(shash_node_t));
	if (new == NULL)
		return (0);
	new->key = strdup(key);
	if (new->key == NULL)
	{
		free(new);
		return (0);
	}
	new->value = strdup(value);
	if (new->value == NULL)
	{
		free(new->key);
		free(new);
		return (0);
	}

	/* insert at head of bucket chain */
	new->next = ht->array[index];
	ht->array[index] = new;

	/* insert into sorted doubly linked list by ASCII order of key */
	if (ht->shead == NULL)
	{
		new->sprev = NULL;
		new->snext = NULL;
		ht->shead = new;
		ht->stail = new;
		return (1);
	}

	curr = ht->shead;
	while (curr && strcmp(curr->key, key) < 0)
		curr = curr->snext;

	if (curr == ht->shead)            /* insert at sorted head */
	{
		new->sprev = NULL;
		new->snext = curr;
		curr->sprev = new;
		ht->shead = new;
	}
	else if (curr == NULL)             /* insert at sorted tail */
	{
		new->sprev = ht->stail;
		new->snext = NULL;
		ht->stail->snext = new;
		ht->stail = new;
	}
	else                               /* insert before curr (middle) */
	{
		new->sprev = curr->sprev;
		new->snext = curr;
		curr->sprev->snext = new;
		curr->sprev = new;
	}
	return (1);
}

/**
 * shash_table_get - Retrieves the value for a key
 * @ht: sorted hash table
 * @key: key to look for
 *
 * Return: value pointer or NULL
 */
char *shash_table_get(const shash_table_t *ht, const char *key)
{
	unsigned long int index;
	shash_node_t *node;

	if (ht == NULL || key == NULL || *key == '\0')
		return (NULL);

	index = key_index((const unsigned char *)key, ht->size);
	for (node = ht->array[index]; node; node = node->next)
		if (strcmp(node->key, key) == 0)
			return (node->value);

	return (NULL);
}

/**
 * shash_table_print - Prints the hash table using the sorted list
 * @ht: sorted hash table
 */
void shash_table_print(const shash_table_t *ht)
{
	shash_node_t *node;
	int comma = 0;

	if (ht == NULL)
		return;

	printf("{");
	for (node = ht->shead; node; node = node->snext)
	{
		if (comma)
			printf(", ");
		printf("'%s': '%s'", node->key, node->value);
		comma = 1;
	}
	printf("}\n");
}

/**
 * shash_table_print_rev - Prints the table in reverse sorted order
 * @ht: sorted hash table
 */
void shash_table_print_rev(const shash_table_t *ht)
{
	shash_node_t *node;
	int comma = 0;

	if (ht == NULL)
		return;

	printf("{");
	for (node = ht->stail; node; node = node->sprev)
	{
		if (comma)
			printf(", ");
		printf("'%s': '%s'", node->key, node->value);
		comma = 1;
	}
	printf("}\n");
}

/**
 * shash_table_delete - Frees the whole sorted hash table
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
#include "hash_tables.h"

/**
 * shash_table_create - Creates a sorted hash table
 * @size: size of the array
 *
 * Return: pointer to new table or NULL
 */
shash_table_t *shash_table_create(unsigned long int size)
{
	shash_table_t *ht;
	unsigned long int i;

	if (size == 0)
		return (NULL);

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
 * shash_table_set - Adds or updates an element in a sorted hash table
 * @ht: pointer to the sorted hash table
 * @key: key string (non-empty)
 * @value: value string (duplicated)
 *
 * Return: 1 on success, 0 on failure
 */
int shash_table_set(shash_table_t *ht, const char *key, const char *value)
{
	unsigned long int index;
	shash_node_t *node, *new, *curr;
	char *val_copy;

	if (ht == NULL || key == NULL || *key == '\0' || value == NULL)
		return (0);

	index = key_index((const unsigned char *)key, ht->size);

	/* update if key already exists in bucket */
	for (node = ht->array[index]; node; node = node->next)
	{
		if (strcmp(node->key, key) == 0)
		{
			val_copy = strdup(value);
			if (val_copy == NULL)
				return (0);
			free(node->value);
			node->value = val_copy;
			return (1);
		}
	}

	/* new node */
	new = malloc(sizeof(shash_node_t));
	if (new == NULL)
		return (0);
	new->key = strdup(key);
	if (new->key == NULL)
	{
		free(new);
		return (0);
	}
	new->value = strdup(value);
	if (new->value == NULL)
	{
		free(new->key);
		free(new);
		return (0);
	}

	/* insert at head of bucket chain */
	new->next = ht->array[index];
	ht->array[index] = new;

	/* insert into sorted doubly linked list by ASCII order of key */
	if (ht->shead == NULL)
	{
		new->sprev = NULL;
		new->snext = NULL;
		ht->shead = new;
		ht->stail = new;
		return (1);
	}

	curr = ht->shead;
	while (curr && strcmp(curr->key, key) < 0)
		curr = curr->snext;

	if (curr == ht->shead)            /* insert at sorted head */
	{
		new->sprev = NULL;
		new->snext = curr;
		curr->sprev = new;
		ht->shead = new;
	}
	else if (curr == NULL)             /* insert at sorted tail */
	{
		new->sprev = ht->stail;
		new->snext = NULL;
		ht->stail->snext = new;
		ht->stail = new;
	}
	else                               /* insert before curr (middle) */
	{
		new->sprev = curr->sprev;
		new->snext = curr;
		curr->sprev->snext = new;
		curr->sprev = new;
	}
	return (1);
}

/**
 * shash_table_get - Retrieves the value for a key
 * @ht: sorted hash table
 * @key: key to look for
 *
 * Return: value pointer or NULL
 */
char *shash_table_get(const shash_table_t *ht, const char *key)
{
	unsigned long int index;
	shash_node_t *node;

	if (ht == NULL || key == NULL || *key == '\0')
		return (NULL);

	index = key_index((const unsigned char *)key, ht->size);
	for (node = ht->array[index]; node; node = node->next)
		if (strcmp(node->key, key) == 0)
			return (node->value);

	return (NULL);
}

/**
 * shash_table_print - Prints the hash table using the sorted list
 * @ht: sorted hash table
 */
void shash_table_print(const shash_table_t *ht)
{
	shash_node_t *node;
	int comma = 0;

	if (ht == NULL)
		return;

	printf("{");
	for (node = ht->shead; node; node = node->snext)
	{
		if (comma)
			printf(", ");
		printf("'%s': '%s'", node->key, node->value);
		comma = 1;
	}
	printf("}\n");
}

/**
 * shash_table_print_rev - Prints the table in reverse sorted order
 * @ht: sorted hash table
 */
void shash_table_print_rev(const shash_table_t *ht)
{
	shash_node_t *node;
	int comma = 0;

	if (ht == NULL)
		return;

	printf("{");
	for (node = ht->stail; node; node = node->sprev)
	{
		if (comma)
			printf(", ");
		printf("'%s': '%s'", node->key, node->value);
		comma = 1;
	}
	printf("}\n");
}

/**
 * shash_table_delete - Frees the whole sorted hash table
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
