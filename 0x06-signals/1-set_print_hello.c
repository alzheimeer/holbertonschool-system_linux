#include "signals.h"

/**
 * print_hello - Function that catch the signal CTRL-C or SIGINT
 * @signal: the signal
 * Return: Nothing
 */
void print_hello(int signal)
{
	(void) signal;
	printf("Hello :)\n");
	fflush(stdout);
}

/**
 * set_print_hello - Function to set the signal handler
 * Return: -1 on error or 0 when success
 */
void set_print_hello(void)
{
	/* Set the handler sor SIGINT or CTRL-C */
	signal(SIGINT, print_hello);
}
