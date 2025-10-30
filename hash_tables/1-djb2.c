#include "hash_tables.h"

/**
 * hash_djb2 - Implements the djb2 hash algorithm
 * @str: Pointer to a (null-terminated) byte string
 *
 * Return: The computed hash as an unsigned long int
 *
 * Description:
 *   Start at 5381 and for each byte c:
 *     hash = ((hash << 5) + hash) + c  ->  hash * 33 + c
 */
unsigned long int hash_djb2(const unsigned char *str)
{
	unsigned long int hash = 5381;
	int c;

	if (str == NULL)
		return (0);

	while ((c = *str++))
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

	return (hash);
}
