#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define BUF_SIZE 1024
#define PERMS 0664

/**
 * print_read_error - print read error and exit 98
 * @file: file name
 */
static void print_read_error(const char *file)
{
	dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", file);
	exit(98);
}

/**
 * print_write_error - print write error and exit 99
 * @file: file name
 */
static void print_write_error(const char *file)
{
	dprintf(STDERR_FILENO, "Error: Can't write to %s\n", file);
	exit(99);
}

/**
 * close_fd - close fd and handle error
 * @fd: file descriptor to close
 */
static void close_fd(int fd)
{
	if (close(fd) == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd);
		exit(100);
	}
}

/**
 * main - copy the content of a file to another file
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: 0 on success, exits with:
 * 97 for wrong usage, 98 for read error, 99 for write error, 100 for close error.
 */
int main(int argc, char *argv[])
{
	int fd_from, fd_to;
	ssize_t rbytes, wbytes;
	char buf[BUF_SIZE];

	if (argc != 3)
	{
		dprintf(STDERR_FILENO, "Usage: cp file_from file_to\n");
		exit(97);
	}

	fd_from = open(argv[1], O_RDONLY);
	if (fd_from == -1)
		print_read_error(argv[1]);

	fd_to = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, PERMS);
	if (fd_to == -1)
	{
		close_fd(fd_from);
		print_write_error(argv[2]);
	}

	while ((rbytes = read(fd_from, buf, BUF_SIZE)) > 0)
	{
		ssize_t total = 0;

		while (total < rbytes)
		{
			wbytes = write(fd_to, buf + total, rbytes - total);
			if (wbytes == -1)
			{
				close_fd(fd_from);
				close_fd(fd_to);
				print_write_error(argv[2]);
			}
			total += wbytes;
		}
	}
	if (rbytes == -1)
	{
		close_fd(fd_from);
		close_fd(fd_to);
		print_read_error(argv[1]);
	}

	close_fd(fd_from);
	close_fd(fd_to);
	return (0);
}
