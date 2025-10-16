#include "lists.h"

/**
 * insert_dnodeint_at_index - inserts a new node at a given position
 * @h: double pointer to the head of the list
 * @idx: index where the new node should be added (starting at 0)
 * @n: value to store in the new node
 *
 * Return: address of the new node, or NULL on failure or if index is invalid
 */
dlistint_t *insert_dnodeint_at_index(dlistint_t **h, unsigned int idx, int n)
{
	dlistint_t *new_node, *tmp;
	unsigned int i;

	if (h == NULL)
		return (NULL);

	/* insert at head */
	if (idx == 0)
		return (add_dnodeint(h, n));

	/* walk to node just before target position (idx - 1) */
	tmp = *h;
	for (i = 0; tmp != NULL && i < idx - 1; i++)
		tmp = tmp->next;

	/* index out of range (too far) */
	if (tmp == NULL)
		return (NULL);

	/* if we are inserting right after the current tail -> use add_dnodeint_end */
	if (tmp->next == NULL)
		return (add_dnodeint_end(h, n));

	/* insert in the middle */
	new_node = malloc(sizeof(dlistint_t));
	if (new_node == NULL)
		return (NULL);

	new_node->n = n;
	new_node->prev = tmp;
	new_node->next = tmp->next;

	tmp->next->prev = new_node;
	tmp->next = new_node;

	return (new_node);
}
