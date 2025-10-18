#include "main.h"

/**
 * _strstr - locates a substring
 * @haystack: the main string to search in
 * @needle: the substring to find
 *
 * Return: pointer to the beginning of the located substring,
 * or NULL if the substring is not found
 */
char *_strstr(char *haystack, char *needle)
{
	char *h, *n;

	if (*needle == '\0')
		return (haystack);

	while (*haystack)
	{
		if (*haystack == *needle)
		{
			h = haystack;
			n = needle;

			while (*h && *n && *h == *n)
			{
				h++;
				n++;
			}

			if (*n == '\0')
				return (haystack);
		}
		haystack++;
	}
	return (0);
}
