#include <stdio.h>
#include <stdlib.h>

/**
 * main - Prints the opcodes of its own main function
 * @argc: The number of command-line arguments
 * @argv: An array containing the command-line arguments
 *
 * Description:
 * This program prints the machine code (opcodes) of its own main
 * function in hexadecimal format. The number of bytes to print is
 * provided as a command-line argument.
 *
 * Return:
 * 0 on success.
 * 1 if the number of arguments is incorrect.
 * 2 if the number of bytes is negative.
 */
int main(int argc, char *argv[])
{
	int bytes, i;
	unsigned char *ptr;

	/* Check if the number of arguments is exactly 2 */
	if (argc != 2)
	{
		printf("Error\n");
		exit(1);
	}

	/* Convert the argument to an integer */
	bytes = atoi(argv[1]);

	/* Check if the number of bytes is negative */
	if (bytes < 0)
	{
		printf("Error\n");
		exit(2);
	}

	/* Point to the beginning of main function in memory */
	ptr = (unsigned char *)main;

	/* Print the opcodes in hexadecimal format */
	for (i = 0; i < bytes; i++)
	{
		printf("%02x", ptr[i]);
		if (i != bytes - 1)
			printf(" ");
	}

	printf("\n");
	return (0);
}
