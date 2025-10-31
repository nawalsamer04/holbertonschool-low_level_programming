#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_tables.h"

/* ---------- small helpers ---------- */
static shash_node_t *make_snode(const char *key, const char *value)
{
	shash_node_t *n = malloc(sizeof(*n));

	if (!n)
		return (NULL);
	n->key = strdup(key);
	if (!n->key)
	{ free(n); return (NULL); }
	n->value = strdup(value ? value : "");
	if (!n->value)
	{ free(n->key); free(n); return (NULL); }
	n->next = NULL;      /* bucket chain (collision list) */
	n->sprev = NULL;     /* sorted doubly list */
	n->snext = NULL;
	return (n);
}

static void insert_sorted(shash_table_t *ht, shash_node_t *node)
{
	shash_node_t *cur;

	if (!ht->shead) /* first element */
	{
		ht->shead = ht->stail = node;
		return;
	}
	/* before current head? */
	if (strcmp(node->key, ht->shead->key) < 0)
	{
		node->snext = ht->shead;
		ht->shead->sprev = node;
		ht->shead = node;
		return;
	}
	/* walk until key is bigger than current */
	cur = ht->shead;
	while (cur->snext && strcmp(node->key, cur->snext->key) > 0)
		cur = cur->snext;

	/* insert after cur (maybe at tail) */
	node->snext = cur->snext;
	node->sprev = cur;
	if (cur->snext)
		cur->snext->sprev = node;
	else
		ht->stail = node;
	cur->snext = node;
}

/* ---------- required API ---------- */
shash_table_t *shash_table_create(unsigned long int size)
{
	shash_table_t *ht = malloc(sizeof(*ht));
	unsigned long int i;

	if (!ht)
		return (NULL);
	ht->size = size;
	ht->array = malloc(sizeof(shash_node_t *) * size);
	if (!ht->array)
	{ free(ht); return (NULL); }
	for (i = 0; i < size; i++)
		ht->array[i] = NULL;
	ht->shead = NULL;
	ht->stail = NULL;
	return (ht);
}

int shash_table_set(shash_table_t *ht, const char *key, const char *value)
{
	unsigned long int idx;
	shash_node_t *n, *p;

	if (!ht || !key || !*key)
		return (0);

	idx = key_index((const unsigned char *)key, ht->size);

	/* update if key exists in bucket */
	for (p = ht->array[idx]; p; p = p->next)
	{
		if (strcmp(p->key, key) == 0)
		{
			char *nv = strdup(value ? value : "");
			if (!nv)
				return (0);
			free(p->value);
			p->value = nv;
			return (1);
		}
	}

	/* new node */
	n = make_snode(key, value);
	if (!n)
		return (0);

	/* add to bucket head (chaining) */
	n->next = ht->array[idx];
	ht->array[idx] = n;

	/* add to sorted doubly linked list */
	insert_sorted(ht, n);
	return (1);
}

char *shash_table_get(const shash_table_t *ht, const char *key)
{
	unsigned long int idx;
	shash_node_t *p;

	if (!ht || !key || !*key)
		return (NULL);

	idx = key_index((const unsigned char *)key, ht->size);
	for (p = ht->array[idx]; p; p = p->next)
		if (strcmp(p->key, key) == 0)
			return (p->value);
	return (NULL);
}

void shash_table_print(const shash_table_t *ht)
{
	const shash_node_t *p;
	int first = 1;

	if (!ht)
		return;

	printf("{");
	for (p = ht->shead; p; p = p->snext)
	{
		if (!first)
			printf(", ");
		printf("'%s': '%s'", p->key, p->value);
		first = 0;
	}
	printf("}\n");
}

void shash_table_print_rev(const shash_table_t *ht)
{
	const shash_node_t *p;
	int first = 1;

	if (!ht)
		return;

	printf("{");
	for (p = ht->stail; p; p = p->sprev)
	{
		if (!first)
			printf(", ");
		printf("'%s': '%s'", p->key, p->value);
		first = 0;
	}
	printf("}\n");
}

void shash_table_delete(shash_table_t *ht)
{
	shash_node_t *p, *tmp;

	if (!ht)
		return;

	/* free using the sorted list once (avoids double frees) */
	p = ht->shead;
	while (p)
	{
		tmp = p->snext;
		free(p->key);
		free(p->value);
		free(p);
		p = tmp;
	}
	free(ht->array);
	free(ht);
}

