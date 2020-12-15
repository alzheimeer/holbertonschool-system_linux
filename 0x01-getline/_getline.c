#include "_getline.h"

/**
 * _getline - reads an entire line from a file descriptor.
 * @fd: is the file descriptor to read from
 * Return: always 0.
 */
char *_getline(const int fd)
{
	char *line, *buf;
	static char *dfd[10];
	static int x;
	static int nfd[10], i[10], j[10], count_size[10];
	int num = 0, existe = 0, idx = 0, b = 0, oldsize = 0;
	int n = 0, k = 0, n_read = 1, f = 0, size = READ_SIZE;

	if (fd == -1)
	{
		x = 0, memset(nfd, 0, 10), memset(i, 0, 10);
		memset(j, 0, 10), memset(count_size, 0, 10);
		while (num < 10)
			dfd[num] = NULL, num++;
		return (NULL);
	}
	while (num < 10)
	{
		if (nfd[num] == fd)
			existe = 1, idx = num;
		if (nfd[num] != 0)
			b++;
		num++;
	}
	if (existe == 0)
		idx = b;
	nfd[idx] = fd;
	if (x == 1)
	{
		x = 0;
		return (NULL);
	}
	buf = malloc(READ_SIZE);
	while (n_read)
	{
		n_read = read(nfd[idx], buf, READ_SIZE);
		if (n_read > 0)
		{
			dfd[idx] = _realloc(dfd[idx], oldsize, size);
			oldsize = size;
			if (f == 0)
				memcpy(dfd[idx], buf, n_read);
			else
				memcpy(dfd[idx] + count_size[idx], buf, n_read);
			size = size + READ_SIZE;
		}
		f++;
		count_size[idx] = n_read + count_size[idx];
	}
	while (dfd[idx][i[idx]] != '\n' && i[idx] != count_size[idx])
		i[idx]++;
	if (i[idx] == j[idx])
		n = 0;
	else
		n = i[idx] - j[idx];
	line = malloc(n + 1);
	memset(line, 0, n + 1);
	for (; j[idx] < i[idx]; j[idx]++)
		line[k] = dfd[idx][j[idx]], k++;
	if (i[idx] == count_size[idx])
	{
		free(dfd[idx]), free(buf), x = 1;
		return (line); /*DEBERIA SER line*/
	}
	i[idx] = i[idx] + 1, j[idx] = i[idx], free(buf);
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
