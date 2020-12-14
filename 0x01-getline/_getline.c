#include "_getline.h"

/**
 * _getline - reads an entire line from a file descriptor.
 * @fd: is the file descriptor to read from
 * Return: always 0.
 */
char *_getline(const int fd)
{	char *line, *buf;
	static char *line1;
	static int i, count_size, j, x, new;
	int n = 0, k = 0, n_read = 1, f = 0, size = READ_SIZE, oldsize = 0;

	if (fd != new)
		free(line1), line1 = NULL, i = 0, count_size = 0, j = 0;
	if (x == 1)
	{	x = 0;
		return (NULL);	}
	buf = malloc(READ_SIZE);
	while (n_read)
	{	n_read = read(fd, buf, READ_SIZE);
		if (n_read > 0)
		{
			line1 = _realloc(line1, oldsize, size);
			oldsize = size;
			if (f == 0)
				memcpy(line1, buf, n_read);
			else
				memcpy(line1 + count_size, buf, n_read);
			size = size + READ_SIZE;	}
		f++, count_size = n_read + count_size;
	}
	if (n_read == 0)
		new = fd;
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
	{	free(line1), free(buf), i = 0, count_size = 0, j = 0, x = 1;
		return (line);	}
	i = i + 1, j = i, free(buf);
	return (line);
}
/**
 * _realloc - realloc() implementation, but different prototype
 * @ptr: pointer to the memory
 * @old_size: old size of the block of memory
 * @new_size: new size of the block of memory
 * Return: new allocated memory block with data copied from previous location
 * NULL on failure
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *array = NULL;
	unsigned int minimum, i;

	if (new_size == old_size)
		return (ptr);
	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}
	array = malloc(new_size);
	if (array == NULL)
	{
		free(ptr);
		return (NULL);
	}
	memset(array, 0, new_size);
	if (ptr == NULL)
	{
		return (array);
	}
	if (new_size > old_size)
		minimum = old_size;
	else
		minimum = new_size;
	for (i = 0; i < minimum; i++)
		array[i] = *((char *)ptr + i);
	free(ptr);
	return ((void *)array);
}
