#include "_getline.h"

/**
 * _getline - reads an entire line from a file descriptor.
 * @fd: is the file descriptor to read from
 * Return: always 0.
 */
char *_getline(const int fd)
{
	char *line = NULL, *buf = NULL;
	static char *line1;
	static int i, count_size, j, x;
	int n = 0, k = 0, n_read = 1, f = 0, size = READ_SIZE;

	if (x == 1)
	{
		free(line1), i = 0, count_size = 0, j = 0, x = 0;
		return (NULL);
	}
	buf = malloc(READ_SIZE);
	while (n_read)
	{
		n_read = read(fd, buf, READ_SIZE);
		if (n_read > 0)
		{
			line1 = realloc(line1, size);
			if (f == 0)
				memcpy(line1, buf, n_read);
			else
				memcpy(line1 + count_size, buf, n_read);
			size = size + READ_SIZE;	}
		f++, count_size = n_read + count_size;
	}
	while (line1[i] != '\n' && i != count_size)
		i++;
	if (i == j)
		n = 0;
	else
		n = i - j;
	line = malloc(n + 1);
	memset(line, 0, n + 1);
	for (; j < i; j++)
		line[k] = line1[j], k++;
	if (i == count_size)
		x = 1;
	i = i + 1;
	j = i;
	free(buf);
	return (line);
}
