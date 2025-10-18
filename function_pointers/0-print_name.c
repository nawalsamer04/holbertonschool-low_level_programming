#include "function_pointers.h"

/**
 * print_name - calls a function on a name string
 * @name: pointer to the name
 * @f: pointer to a function that prints the name
 *
 * Return: nothing
 */
void print_name(char *name, void (*f)(char *))
{
	if (name == NULL || f == NULL)
		return;

	f(name);
}
