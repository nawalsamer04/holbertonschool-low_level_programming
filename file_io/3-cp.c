#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUF_SIZE 1024

/**
 * print_read_error - print read error and exit 98
 * @file: file name
 */
void print_read_error(const char *file)
{
	dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", file);
	exit(98);
}

/**
 * print_write_error - print write error and exit 99
 * @file: file name
 */
void print_write_error(const char *file)
{
	dprintf(STDERR_FILENO, "Error: Can't write to %s\n", file);
	exit(99);
}

/**
 * close_fd - close fd or exit 100 on failure
 * @fd: file descriptor
 */
void close_fd(int fd)
{
	if (close(fd) == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd);
		exit(100);
	}
}

/**
 * main - copy the content of a file to another
 * @ac: arg count
 * @av: arg vector
 * Return: 0 on success
 */
int main(int ac, char **av)
{
	int fd_from, fd_to;
	ssize_t r, w;
	char buf[BUF_SIZE];

	if (ac != 3)
	{
		dprintf(STDERR_FILENO, "Usage: cp file_from file_to\n");
		exit(97);
	}

	fd_from = open(av[1], O_RDONLY);
	if (fd_from == -1)
		print_read_error(av[1]);

	fd_to = open(av[2], O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (fd_to == -1)
		print_write_error(av[2]);

	while (1)
	{
		r = read(fd_from, buf, BUF_SIZE);
		if (r == -1)
			print_read_error(av[1]);
		if (r == 0)
			break;

		w = write(fd_to, buf, r);
		if (w == -1 || w != r)
			print_write_error(av[2]);
	}

	close_fd(fd_from);
	close_fd(fd_to);
	return (0);
}

