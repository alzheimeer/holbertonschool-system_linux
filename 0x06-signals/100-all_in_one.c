#include "signals.h"

/**
 * sigaction_handler - signal handler with 3 arguments
 * @sig: signal number
 * @info: a structure containing further information about the signal
 * @ucontext: this field contains signal context information that was
 * saved on the user-space stack by the kernel
 */
void sigaction_handler(int sig, siginfo_t *info, void *ucontext)
{
	UNUSED(sig);
	UNUSED(ucontext);
	psiginfo(info, "Caught");
}

/**
 * all_in_one - handles all signals
 * Return: Nothing
 */
void all_in_one(void)
{
	struct sigaction act;
	int i;

	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = sigaction_handler;

	for (i = 1; i < NSIG; ++i)
		sigaction(i, &act, NULL);
}
