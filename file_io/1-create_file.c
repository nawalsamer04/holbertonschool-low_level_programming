#include "main.h"

/**
 * create_file - creates/truncates a file and writes text
 * @filename: file name
 * @text_content: NULL-terminated string to write (may be NULL)
 * Return: 1 on success, -1 on failure
 */
int create_file(const char *filename, char *text_content)
{
	int fd;
	ssize_t w = 0, len = 0;

	if (!filename)
		return (-1);

	if (text_content)
		while (text_content[len])
			len++;

	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd == -1)
		return (-1);

	if (len)
	{
		w = write(fd, text_content, len);
		if (w == -1 || w != len)
		{
			close(fd);
			return (-1);
		}
	}

	if (close(fd) == -1)
		return (-1);

	return (1);
}

