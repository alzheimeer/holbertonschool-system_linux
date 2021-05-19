#include "multithreading.h"
#include <stdio.h>

/**
 * thread_entry -  serves as the entry point to a new thread
 * @arg: holds the address of a string that must be printed
 * and followed by a new line
 * Return: ???
*/
void *thread_entry(void *arg)
{
	if (!arg)
		return (NULL);
	printf("%s\n", (char *)arg);
	pthread_exit(0);
}
