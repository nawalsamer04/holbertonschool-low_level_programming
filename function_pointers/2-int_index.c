#include "function_pointers.h"

/**
 * int_index - searches for an integer
 * @array: pointer to array
 * @size: number of elements in array
 * @cmp: pointer to function used to compare values
 *
 * Return: index of first element for which cmp does not return 0,
 *         -1 if no match or if size <= 0, or if array/cmp is NULL
 */
int int_index(int *array, int size, int (*cmp)(int))
{
	int i;

	if (array == NULL || cmp == NULL || size <= 0)
		return (-1);

	for (i = 0; i < size; i++)
	{
		if (cmp(array[i]) != 0)
			return (i);
	}

	return (-1);
}
