#include "lists.h"
#include <string.h>

/**
 * add_node - adds a new node at the beginning of a list_t list
 * @head: double pointer to the head of the list
 * @str: string to duplicate and store in the new node
 *
 * Return: address of the new element, or NULL if it failed
 */
list_t *add_node(list_t **head, const char *str)
{
	list_t *new_node;
	unsigned int len = 0;

	new_node = malloc(sizeof(list_t));
	if (new_node == NULL)
		return (NULL);

	if (str != NULL)
	{
		new_node->str = strdup(str);
		while (str[len])
			len++;
		new_node->len = len;
	}
	else
	{
		new_node->str = NULL;
		new_node->len = 0;
	}

	new_node->next = *head;
	*head = new_node;

	return (new_node);
}
