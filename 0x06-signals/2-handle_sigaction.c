#include "signals.h"

/**
 * signal_handler - receives signal
 * @signum: the signal number received
 */
void signal_handler(int signum)
{
	printf("Gotcha! [%d]\n", signum);
	fflush(stdout);
}
/**
 * handle_sigaction - applies sigaction syscall
 * Return: 0 on success else -1
 */
int handle_sigaction(void)
{
	struct sigaction pepe;

	memset(&pepe, 0, sizeof(pepe));
	pepe.sa_handler = signal_handler;
	return (sigaction(SIGINT, &pepe, NULL));
}
