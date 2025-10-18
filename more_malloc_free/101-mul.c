#include <stdlib.h>

/* The checker links _putchar.c for us */
int _putchar(char c);

/**
 * _strlen - compute string length
 * @s: string
 * Return: length
 */
static int _strlen(char *s)
{
	int n = 0;

	while (s && s[n])
		n++;
	return (n);
}

/**
 * is_digits - check that a string contains only decimal digits
 * @s: string
 * Return: 1 if all digits, 0 otherwise
 */
static int is_digits(char *s)
{
	int i = 0;

	if (s == NULL || *s == '\0')
		return (0);
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

/**
 * print_error_and_exit - print "Error\n" and exit(98)
 */
static void print_error_and_exit(void)
{
	_putchar('E');
	_putchar('r');
	_putchar('r');
	_putchar('o');
	_putchar('r');
	_putchar('\n');
	exit(98);
}

/**
 * print_number_array - print a number stored as an int array of digits
 * @a: digits array (each 0..9)
 * @n: number of digits in a
 */
static void print_number_array(int *a, int n)
{
	int i = 0;

	/* skip leading zeros but leave one zero if number is 0 */
	while (i < n - 1 && a[i] == 0)
		i++;

	for (; i < n; i++)
		_putchar(a[i] + '0');
	_putchar('\n');
}

/**
 * main - multiply two positive numbers given as strings
 * @ac: argument count
 * @av: argument vector
 * Return: 0 on success, 98 on error (via exit)
 */
int main(int ac, char **av)
{
	char *s1, *s2;
	int len1, len2, size, i, j;
	int *res;

	if (ac != 3)
		print_error_and_exit();

	s1 = av[1];
	s2 = av[2];

	if (!is_digits(s1) || !is_digits(s2))
		print_error_and_exit();

	len1 = _strlen(s1);
	len2 = _strlen(s2);
	size = len1 + len2;

	res = (int *)calloc((size_t)size, sizeof(int));
	if (res == NULL)
		print_error_and_exit();

	/* classic long multiplication from right to left */
	for (i = len1 - 1; i >= 0; i--)
	{
		int d1 = s1[i] - '0';

		for (j = len2 - 1; j >= 0; j--)
		{
			int d2 = s2[j] - '0';
			int pos_low = i + j + 1;
			int pos_hi = i + j;
			int sum = d1 * d2 + res[pos_low];

			res[pos_low] = sum % 10;
			res[pos_hi] += sum / 10;
		}
	}

	print_number_array(res, size);
	free(res);
	return (0);
}
