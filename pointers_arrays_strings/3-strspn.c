#include "main.h"

/**
 * _strspn - gets the length of a prefix substring
 * @s: string to scan
 * @accept: string containing allowed characters
 *
 * Return: number of bytes in the initial segment of s
 * which consist only of bytes from accept
 */
unsigned int _strspn(char *s, char *accept)
{
	unsigned int count = 0;
	char *a;
	int match;

	while (*s)
	{
		match = 0;
		for (a = accept; *a; a++)
		{
			if (*s == *a)
			{
				match = 1;
				break;
			}
		}
		if (!match)
			break;
		count++;
		s++;
	}
	return (count);
}
