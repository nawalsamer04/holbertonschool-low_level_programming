#include "lists.h"

/**
 * sum_dlistint - returns the sum of all data (n) of a dlistint_t list
 * @head: pointer to the head of the list
 *
 * Return: sum of all n values, or 0 if the list is empty
 */
int sum_dlistint(dlistint_t *head)
{
	int sum = 0;

	while (head)
	{
		sum += head->n;
		head = head->next;
	}
	return (sum);
}
