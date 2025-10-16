#ifndef LISTS_H
#define LISTS_H

#include <stdlib.h>

/**
 * struct list_s - singly linked list node
 * @str: string (malloc'ed)
 * @len: length of the string
 * @next: pointer to the next node
 */
typedef struct list_s
{
	char *str;
	unsigned int len;
	struct list_s *next;
} list_t;

/**
 * print_list - prints all elements of a list_t list
 * @h: pointer to the list
 * Return: number of nodes
 */
size_t print_list(const list_t *h);
size_t list_len(const list_t *h);

/**
 * _putchar - writes a character to stdout
 * @c: the character to print
 * Return: 1 on success, -1 on error
 */
int _putchar(char c);

#endif /* LISTS_H */

