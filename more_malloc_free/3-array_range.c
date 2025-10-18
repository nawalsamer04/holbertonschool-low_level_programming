#include <stdlib.h>
#include "main.h"

/**
 * array_range - creates an array of ints from min to max (inclusive)
 * @min: starting value
 * @max: ending value
 *
 * Return: pointer to new array, or NULL if min > max or malloc fails
 */
int *array_range(int min, int max)
{
	int *a;
	int len, i;

	if (min > max)
		return (NULL);

	len = max - min + 1;

	a = malloc(sizeof(int) * len);
	if (a == NULL)
		return (NULL);

	for (i = 0; i < len; i++)
		a[i] = min + i;

	return (a);
}
