#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUF_SIZE 1024
/**
 * print_read_error - prints read error message and exits
 * @file: name of the file that can't be read
 */
void print_read_error(const char *file)
{
	dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", file);
	exit(98);
}
/**
 * print_write_error - prints write error message and exits
 * @file: name of the file that can't be written
 */
void print_write_error(const char *file)
{
	dprintf(STDERR_FILENO, "Error: Can't write to %s\n", file);
	exit(99);
}
/**
 * close_fd - closes a file descriptor
 * @fd: the file descriptor to close
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
 * main - copies the contents of one file to another
 * @ac: argument count
 * @av: argument vector
 *
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

	while ((r = read(fd_from, buf, BUF_SIZE)) > 0)
	{
		w = write(fd_to, buf, r);
		if (w == -1 || w != r)
			print_write_error(av[2]);
	}

	if (r == -1)
		print_read_error(av[1]);

	close_fd(fd_from);
	close_fd(fd_to);
	return (0);
}

