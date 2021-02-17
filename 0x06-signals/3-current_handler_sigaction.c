#include "signals.h"

/**
 * current_handler_sigaction - retrieves handler by sigaction
 * Return: current handler or NULL
 */
void (*current_handler_sigaction(void))(int)
{
	struct sigaction oldpepe;

	if (sigaction(SIGINT, NULL, &oldpepe) == -1)
		return (NULL);

	return (oldpepe.sa_handler);
}
