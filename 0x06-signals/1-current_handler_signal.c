#include "signals.h"

/**
 * current_handler_signal - retrieves the current handler of the signal SIGINT
 * @void: void
 * Return: not
 */
void (*current_handler_signal(void))(int)
{
	void (*handler)(int);

	handler = signal(SIGINT, NULL);
	signal(SIGINT, handler);

	return (handler);
}
