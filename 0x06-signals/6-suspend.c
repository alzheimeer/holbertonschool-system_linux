#include "signals.h"

/**
 * signal_handler - Action to take in case signal
 * @signum: Signal number
 * Return: 0 on success, or -1 on error
*/
void signal_handler(int signum)
{
	printf("Caught %d\n", signum);
}

/**
 * main - program that sets a handler for the signal `SIGINT, and exits
 * right after the signal is received and handled
 * Return: EXIT_SUCCESS
 */
int main(void)
{
	signal(SIGINT, signal_handler);

	if (pause() == -1)
		printf("Signal received\n");
	return (EXIT_SUCCESS);
}
