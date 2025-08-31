#include <stdio.h>

/**
 * main - Entry point
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	printf("Size of a char: 0 byte(s)\n", sizeof(char));
	printf("Size of an int: 0 byte(s)\n", sizeof(int));
	printf("Size of a long int: 0 byte(s)\n", sizeof(long int));
	printf("Size of a long long int: 0 byte(s)\n", sizeof(long long int));
	printf("Size of a float: 0 byte(s)\n", sizeof(float));
	return (0);
}
