#include "lists.h"

/**
 * delete_dnodeint_at_index - deletes the node at a given index
 * of a dlistint_t list
 * @head: double pointer to the head of the list
 * @index: index of the node that should be deleted (starting at 0)
 *
 * Return: 1 if it succeeded, -1 if it failed
 */
int delete_dnodeint_at_index(dlistint_t **head, unsigned int index)
{
	dlistint_t *node;

	if (head == NULL || *head == NULL)
		return (-1);

	/* Delete head */
	if (index == 0)
	{
		node = *head;
		*head = node->next;
		if (*head != NULL)
			(*head)->prev = NULL;
		free(node);
		return (1);
	}

	/* Walk to the node at `index` */
	node = *head;
	while (index && node != NULL)
	{
		node = node->next;
		index--;
	}

	/* Out of range */
	if (node == NULL)
		return (-1);

	/* Relink neighbors */
	if (node->prev)
		node->prev->next = node->next;
	if (node->next)
		node->next->prev = node->prev;

	free(node);
	return (1);
}
