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
	pid_t pid;

	UNUSED(sig);
	UNUSED(ucontext);
	pid = info->si_pid;
	printf("SIGQUIT sent by %d\n", pid);
}

/**
 * trace_signal_sender - shows the pid of the process which sent SIGQUIT
 * Return: 0 on success, or -1 on error
 */
int trace_signal_sender(void)
{
	struct sigaction act;

	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = sigaction_handler;

	return (sigaction(SIGQUIT, &act, NULL));
}
