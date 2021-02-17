#include "signals.h"

/**
 * sigset_init -  initializes a sigset
 * @set: is a pointer to the signal set to initialize
 * @signals: is a 0-terminated array of int, each one being a signal number
 * Return: 0 on success, or -1 on error
 */
int sigset_init(sigset_t *set, int *signals)
{
	int i;

	if (sigemptyset(set) == -1)
		return (-1);

	for (i = 0; signals[i]; ++i)
	{
		if (sigaddset(set, signals[i]) == -1)
			return (-1);
	}

	return (0);
}
