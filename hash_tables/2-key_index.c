#include "hash_tables.h"

/**
 * key_index - gives the index of a key
 * @key: key (string) to hash
 * @size: size of the array of the hash table
 * Return: index where key/value pair should be stored
 *
 * Description: uses the djb2 algorithm for hashing
 */
unsigned long int key_index(const unsigned char *key, unsigned long int size)
{
	/* 1 Tab before this declaration */
	unsigned long int hash;

	/* 1 Tab before if, 2 Tabs inside its body */
	if (key == NULL || size == 0)
		return (0);

	hash = hash_djb2(key);
	return (hash % size);
}

