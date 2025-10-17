#include "main.h"

#define BUFSIZE 1024

static void close_fd(int fd)
{
	if (close(fd) == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd);
		exit(100);
	}
}

/**
 * main - cp file_from file_to
 * @ac: argument count
 * @av: argument vector
 * Return: 0 on success; exits with 97/98/99/100 on error
 */
int main(int ac, char **av)
{
	int fd_from, fd_to;
	ssize_t r, w;
	char buf[BUFSIZE];

	if (ac != 3)
	{
		dprintf(STDERR_FILENO, "Usage: cp file_from file_to\n");
		exit(97);
	}

	fd_from = open(av[1], O_RDONLY);
	if (fd_from == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", av[1]);
		exit(98);
	}

	fd_to = open(av[2], O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (fd_to == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't write to %s\n", av[2]);
		close_fd(fd_from);
		exit(99);
	}

	while ((r = read(fd_from, buf, BUFSIZE)) != 0)
	{
		if (r == -1)
		{
			dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", av[1]);
			close_fd(fd_from);
			close_fd(fd_to);
			exit(98);
		}

		ssize_t total = 0;
		while (total < r)
		{
			w = write(fd_to, buf + total, r - total);
			if (w == -1)
			{
				dprintf(STDERR_FILENO, "Error: Can't write to %s\n", av[2]);
				close_fd(fd_from);
				close_fd(fd_to);
				exit(99);
			}
			total += w;
		}
	}

	close_fd(fd_from);
	close_fd(fd_to);
	return (0);
}

