#include "variadic_functions.h"

/**
 * print_strings - prints strings followed by a new line
 * @separator: string printed between strings (ignored if NULL)
 * @n: number of strings passed to the function
 *
 * Description: if a string argument is NULL, print "(nil)" instead.
 */
void print_strings(const char *separator, const unsigned int n, ...)
{
	va_list ap;
	unsigned int i;

	va_start(ap, n);

	for (i = 0; i < n; i++)
	{
		char *s = va_arg(ap, char *);

		if (s == NULL)
			printf("(nil)");
		else
			printf("%s", s);

		if (separator != NULL && i != (n - 1))
			printf("%s", separator);
	}

	printf("\n");
	va_end(ap);
}
