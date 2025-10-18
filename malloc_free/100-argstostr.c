#include <stdlib.h>
#include "main.h"

/**
 * argstostr - concatenates all the arguments of the program
 * @ac: argument count
 * @av: argument vector
 *
 * Return: pointer to a new string containing all args separated by '\n',
 *         or NULL on failure or if ac == 0 or av == NULL.
 */
char *argstostr(int ac, char **av)
{
	int i, j, k, total_len = 0;
	char *s;

	if (ac == 0 || av == NULL)
		return (NULL);

	/* 1) compute total length = sum of all chars + one '\n' per arg */
	for (i = 0; i < ac; i++)
	{
		if (av[i] != NULL)
		{
			for (j = 0; av[i][j] != '\0'; j++)
				total_len++;
		}
		total_len++; /* for the trailing '\n' after this arg */
	}

	/* +1 for the final '\0' */
	s = (char *)malloc((total_len + 1) * sizeof(char));
	if (s == NULL)
		return (NULL);

	/* 2) copy args and insert '\n' after each */
	k = 0;
	for (i = 0; i < ac; i++)
	{
		if (av[i] != NULL)
		{
			for (j = 0; av[i][j] != '\0'; j++)
				s[k++] = av[i][j];
		}
		s[k++] = '\n';
	}

	s[k] = '\0';
	return (s);
}
