#include "variadic_functions.h"

/**
 * print_numbers - prints numbers followed by a new line
 * @separator: string printed between numbers
 * @n: number of integers passed to the function
 *
 * Description: If separator is NULL, don’t print it.
 * Print a new line at the end of the function.
 */
void print_numbers(const char *separator, const unsigned int n, ...)
{
	va_list ap;
	unsigned int i;

	va_start(ap, n);

	for (i = 0; i < n; i++)
	{
		printf("%d", va_arg(ap, int));
		if (separator != NULL && i != (n - 1))
			printf("%s", separator);
	}

	printf("\n");
	va_end(ap);
}
