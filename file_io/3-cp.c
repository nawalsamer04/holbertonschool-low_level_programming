#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUF_SIZE 1024

/**
 * print_read_error - print read error message to STDERR.
 * @name: file name that couldn't be read
 */
static void print_read_error(const char *name)
{
	dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", name);
}

/**
 * print_write_error - print write/creation error message to STDERR.
 * @name: file name that couldn't be written/created
 */
static void print_write_error(const char *name)
{
	dprintf(STDERR_FILENO, "Error: Can't write to %s\n", name);
}

/**
 * safe_close - close a file descriptor, exit(100) if it fails.
 * @fd: file descriptor to close
 */
static void safe_close(int fd)
{
	if (close(fd) == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd);
		exit(100);
	}
}

/**
 * main - copy the content of a file to another file.
 * @ac: argument count
 * @av: argument vector
 *
 * Return: 0 on success, exits with specific codes on errors.
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
	{
		print_read_error(av[1]);
		exit(98);
	}

	fd_to = open(av[2], O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (fd_to == -1)
	{
		print_write_error(av[2]);
		safe_close(fd_from);
		exit(99);
	}

	while ((r = read(fd_from, buf, BUF_SIZE)) > 0)
	{
		w = write(fd_to, buf, r);
		if (w == -1 || w != r)
		{
			print_write_error(av[2]);
			safe_close(fd_from);
			safe_close(fd_to);
			exit(99);
		}
	}
	if (r == -1)
	{
		print_read_error(av[1]);
		safe_close(fd_from);
		safe_close(fd_to);
		exit(98);
	}

	safe_close(fd_from);
	safe_close(fd_to);
	return (0);
}

