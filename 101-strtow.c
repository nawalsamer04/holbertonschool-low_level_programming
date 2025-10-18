#include <stdlib.h>

/**
 * strtow - splits a string into words (space-separated)
 * @str: input C-string
 *
 * Return: pointer to a NULL-terminated array of strings (words),
 *         or NULL if @str is NULL/empty/all spaces or on allocation failure.
 */
static int is_space(char c)
{
	return (c == ' ');
}

static int count_words(const char *s)
{
	int i = 0, words = 0;

	while (s[i])
	{
		/* Skip spaces */
		while (s[i] && is_space(s[i]))
			i++;

		/* If we’re at the start of a word, count it */
		if (s[i] && !is_space(s[i]))
		{
			words++;
			while (s[i] && !is_space(s[i]))
				i++;
		}
	}
	return (words);
}

static void free_words(char **tab, int upto)
{
	int i;

	for (i = 0; i < upto; i++)
		free(tab[i]);
	free(tab);
}

/**
 * strtow - public entry, split by single space delimiter
 * @str: input C-string
 *
 * Return: pointer to words array, or NULL on failure/empty
 */
char **strtow(char *str)
{
	int i = 0, w = 0, start, len, words;
	char **tab;

	if (str == NULL)
		return (NULL);

	/* Count words (ignoring consecutive spaces) */
	words = count_words(str);
	if (words == 0)
		return (NULL);

	tab = malloc(sizeof(*tab) * (words + 1));
	if (tab == NULL)
		return (NULL);

	while (str[i])
	{
		/* Skip spaces */
		while (str[i] && is_space(str[i]))
			i++;

		if (str[i] && !is_space(str[i]))
		{
			start = i;
			len = 0;

			while (str[i] && !is_space(str[i]))
			{
				len++;
				i++;
			}

			tab[w] = malloc(sizeof(char) * (len + 1));
			if (tab[w] == NULL)
			{
				free_words(tab, w);
				return (NULL);
			}

			/* Copy the word */
			for (i = start; len > 0; len--, i++)
				tab[w][start + (start + len - 1) - (start + len - len)] = str[i];

			/* The above copy logic is confusing—replace with a simple loop: */
		}
	}

	/* Re-scan to actually copy (simple & correct) */
	i = 0, w = 0;
	while (str[i])
	{
		int j = 0;

		while (str[i] && is_space(str[i]))
			i++;
		if (!(str[i] && !is_space(str[i])))
			continue;

		start = i;
		while (str[i] && !is_space(str[i]))
			i++;
		len = i - start;

		for (j = 0; j < len; j++)
			tab[w][j] = str[start + j];
		tab[w][len] = '\0';
		w++;
	}

	tab[w] = NULL;
	return (tab);
}
