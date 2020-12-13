#include "_getline.h"

/**
 * _getline - reads an entire line from a file descriptor.
 * @fd: is the file descriptor to read from
 * Return: always 0.
 */
char *_getline(const int fd)
{
	char *line = NULL;
	static char buf[READ_SIZE] = {0};
	static int i, j, x;
	int n = 0, k = 0;

	if (x == 1)
	{
		memset(buf, '$', 1024);
		i = 0, j = 0, x = 0;
		return (NULL);
	}
	if (i == 0)
		read(fd, buf, READ_SIZE);

	for (; buf[i] != '\n' && buf[i] != '\0'; i++)
		;

	if (i == j)
		n = 0;
	else
		n = i - j;

	line = malloc(n + 1);
	if (line == NULL)
		return (NULL);
	memset(line, 0, n + 1);

	for (; j < i; j++)
	{
		line[k] = buf[j];
		k++;
	}

	if (buf[i + 1] == '\0')
		x = 1;

	i = i + 1;
	j = i;

	return (line);
}
