#include "main.h"
#include <stdio.h>

/**
 * print_diagsums - prints sums of the two diagonals of a square matrix
 * @a: pointer to first element of the matrix (stored in 1D)
 * @size: side length of the square matrix
 */
void print_diagsums(int *a, int size)
{
	long sum1 = 0;
	long sum2 = 0;
	int i;

	for (i = 0; i < size; i++)
	{
		sum1 += a[i * size + i];                 /* main diagonal */
		sum2 += a[i * size + (size - 1 - i)];    /* anti-diagonal */
	}
	printf("%ld, %ld\n", sum1, sum2);
}
