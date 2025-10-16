#ifndef LISTS_H
#define LISTS_H

#include <stdlib.h>

/**
 * struct list_s - singly linked list
 * @str: string (malloc'ed)
 * @len: length of the string
 * @next: points to the next node
 */
typedef struct list_s
{
	char *str;
	unsigned int len;
	struct list_s *next;
} list_t;

/* prototypes */
size_t print_list(const list_t *h);

int _putchar(char c); /* provided by checker */

#endif /* LISTS_H */
