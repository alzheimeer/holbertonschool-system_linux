#include "_getline.h"
#define OLD_SIZE (current_file->old_size)
#define NEW_SIZE (readed + OLD_SIZE)
#define CLEAN_CUR_O (free(current_file->output), current_file->output = NULL)
static streamf *file, *current_file;
/**
 * _getline - Gets a line from an input
 * @fd: file descriptor number
 *
 * Return: pointer to the memory
 */
char *_getline(const int fd)
{
	int readed = 0, index = 0;
	char buffer[READ_SIZE], *line = NULL, *temp = NULL;

	if (fd == -1)
	{
		clean_files();
		return (NULL);
	}
	if (!handlefd(fd))
		return (NULL);
	do {
		readed = read(current_file->fd, &buffer, READ_SIZE);
		if (readed == -1)
			return (NULL);
		if (readed)
		{
			temp = _realloc(current_file->output, OLD_SIZE, NEW_SIZE);
			if (temp == NULL)
				return (NULL);
			current_file->output = temp;
			memcpy(current_file->output + OLD_SIZE, buffer, readed);
			OLD_SIZE = NEW_SIZE;
		}
		index = getindex(current_file->output, 10);
	} while (readed == READ_SIZE && index == -1);
	if (index != -1 && current_file->output)
		return (split_line(index));
	if (OLD_SIZE)
	{
		line = malloc(OLD_SIZE + 1);
		if (line == NULL)
			return (NULL);
		memcpy(line, current_file->output, OLD_SIZE), line[OLD_SIZE] = 0;
		OLD_SIZE = 0, free(current_file->output), current_file->output = NULL;
		return (line);
	}
	if (!file->next)
		CLEAN_CUR_O, free(file), file = NULL;
	return (NULL);
}
/**
 * getindex - search for a character inside an array
 * @array: array to search the character from
 * @chr: character to search for
 * Return: index of the chr in array or -1 if not found
 */
int getindex(char *array, char chr)
{
	unsigned int index = 0, first_found = 1, ret_index = -1;

	if (!array)
		return (-1);
	for (index = 0; index < OLD_SIZE; index++)
	{
		if (array[index] == chr)
		{
			if (first_found)
			{
				ret_index = index;
				first_found = 0;
			}
		}
	}
	return (ret_index);
}
/**
 *_realloc - array with the range of integer
 *@ptr: array
 *@old_size: old array sizee
 *@new_size: new array size
 *Return: int array with min to max
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
/**
 *handlefd - returns saved stream or created stream if not found
 *@fd: file descriptor number
 *
 *Return: NULL if something failed
 *
 */
streamf *handlefd(unsigned int fd)
{
	streamf *initial = NULL;

	current_file = file;
	initial = file;
	while (current_file)
	{
		if (fd == current_file->fd)
			break;
		current_file = current_file->next;
	}
	if (!current_file)
	{
		file = malloc(sizeof(streamf));
		if (!file)
			return (NULL);
		file->next = initial;
		file->fd = fd;
		file->output = NULL;
		file->old_size = 0;
		current_file = file;
	}
	return (file);
}
/**
 *split_line - split line until new line character is found
 *@index: index of current solution
 *
 *Return: String used by split line
 *
 */
char *split_line(int index)
{
	char *line = NULL, *temp = NULL;

	line = malloc(index + 1);
	if (line == NULL)
		return (NULL);
	memcpy(line, current_file->output, index);
	line[index] = 0;
	if (!OLD_SIZE)
	{
		free(current_file->output);
		current_file->output = NULL;
		current_file->old_size = 0;
	}
	else
	{
		OLD_SIZE = OLD_SIZE - index - 1;
		temp = malloc(OLD_SIZE);
		if (!temp)
			return (NULL);
		memcpy(temp, current_file->output + index + 1, OLD_SIZE);
		free(current_file->output);
		current_file->output = temp;
	}
	return (line);
}
/**
 *clean_files - cleans all files allocs
 */
void clean_files(void)
{
	streamf *temp;

	while (file)
	{
		temp = file->next;
		if (file->output)
		{
			free(file->output);
			file->output = NULL;
		}
		free(file);
		file = temp;
	}
	current_file = NULL;
	file = NULL;
}
