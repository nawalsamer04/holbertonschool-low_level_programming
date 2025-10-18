#ifndef VARIADIC_FUNCTIONS_H
#define VARIADIC_FUNCTIONS_H

#include <stdarg.h>

/**
 * sum_them_all - Return the sum of all parameters.
 * @n: number of following arguments.
 *
 * Return: sum of the arguments, or 0 if @n is 0.
 */
int sum_them_all(const unsigned int n, ...);

#endif /* VARIADIC_FUNCTIONS_H */
