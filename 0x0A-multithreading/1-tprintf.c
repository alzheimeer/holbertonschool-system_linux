#include "multithreading.h"

/**
 * tprintf - uses printf family to print out a given formatted string
 * @format: data to print
 * Return: EXIT_SUCCESS
 */
int tprintf(char const *format, ...)
{
	printf("[%lu] %s", pthread_self(), format);
	return (EXIT_SUCCESS);
}
