#include "signals.h"

/**
 * handle_pending - handle pending signals
 * @handler: Signal handler function
 * Return: 0 on success, or -1 on error
 */
int handle_pending(void (*handler)(int))
{
	int sign;
	sigset_t set;
	struct sigaction sig;

	sig.sa_handler = handler;

	if (sigpending(&set) == -1)
		return (-1);

	for (sign = 1; sign < NSIG; ++sign)
		if (sigismember(&set, sign))
			if (sigaction(sign, &sig, NULL) == -1)
				return (-1);
	return (0);
}
