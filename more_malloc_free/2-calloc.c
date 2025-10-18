#include <stdlib.h>
#include <limits.h>
#include "main.h"

/**
 * _calloc - allocates zero-initialized memory for an array
 * @nmemb: number of elements
 * @size:  size of each element in bytes
 *
 * Return: pointer to allocated zeroed memory,
 *         or NULL if nmemb or size is 0, on overflow, or on malloc failure
 */
void *_calloc(unsigned int nmemb, unsigned int size)
{
	size_t bytes, i;
	unsigned char *p;

	/* invalid sizes */
	if (nmemb == 0 || size == 0)
		return (NULL);

	/* overflow check: nmemb * size must not wrap */
	if (nmemb > SIZE_MAX / size)
		return (NULL);

	bytes = (size_t)nmemb * (size_t)size;

	p = malloc(bytes);
	if (p == NULL)
		return (NULL);

	/* manual zeroing to stay portable under C89 */
	for (i = 0; i < bytes; i++)
		p[i] = 0;

	return ((void *)p);
}
