#ifndef FUNCTION_POINTERS_H
#define FUNCTION_POINTERS_H

#include <stddef.h>

/**
 * print_name - call a callback to print a name
 * @name: the name string
 * @f:    function pointer taking (char *) and returning void
 *
 * Description: If either argument is NULL, the function does nothing.
 */
void print_name(char *name, void (*f)(char *));

#endif /* FUNCTION_POINTERS_H */
