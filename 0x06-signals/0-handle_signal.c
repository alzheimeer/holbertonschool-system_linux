#include "signals.h"

/**
 * sig_handler - Entry point
 * @signum: dsadasd
 * Return: not
 */
void sig_handler(int signum)
{
	printf("Gotcha! [%d]\n", signum);
}

/**
 * handle_signal - Entry point
 *
 * Return: -1 error
 */
int handle_signal(void)
{
	if (signal(SIGINT, sig_handler) == SIG_ERR)
		return (-1);
	return (0);
}
