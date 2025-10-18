#include "main.h"
#include <stdlib.h>

/**
 * alloc_grid - allocate a 2D grid of ints and initialize to 0
 * @width:  number of columns
 * @height: number of rows
 *
 * Return: pointer to the 2D array (height x width), or NULL on failure
 *         Also returns NULL if width or height is <= 0.
 */
int **alloc_grid(int width, int height)
{
	int **grid;
	int r, c;

	if (width <= 0 || height <= 0)
		return (NULL);

	/* allocate array of row pointers */
	grid = (int **)malloc(sizeof(int *) * height);
	if (grid == NULL)
		return (NULL);

	/* allocate each row and initialize to 0 */
	for (r = 0; r < height; r++)
	{
		grid[r] = (int *)malloc(sizeof(int) * width);
		if (grid[r] == NULL)
		{
			/* free any rows already allocated, then the row-ptr array */
			while (r--)
				free(grid[r]);
			free(grid);
			return (NULL);
		}

		for (c = 0; c < width; c++)
			grid[r][c] = 0;
	}

	return (grid);
}
