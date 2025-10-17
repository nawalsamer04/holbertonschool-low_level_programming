#include "main.h"

/**
 * read_textfile - reads a file and prints to STDOUT
 * @filename: path to file
 * @letters: max bytes to read/print
 * Return: number of bytes printed, or 0 on failure
 */
ssize_t read_textfile(const char *filename, size_t letters)
{
	ssize_t fd, r, w, total = 0;
	char *buf;

	if (!filename || letters == 0)
		return (0);

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (0);

	buf = malloc(letters);
	if (!buf)
	{
		close(fd);
		return (0);
	}

	r = read(fd, buf, letters);
	if (r <= 0)
	{
		free(buf);
		close(fd);
		return (0);
	}

	while (total < r)
	{
		w = write(STDOUT_FILENO, buf + total, r - total);
		if (w == -1)
		{
			free(buf);
			close(fd);
			return (0);
		}
		total += w;
	}

	free(buf);
	close(fd);
	return (total);
}

