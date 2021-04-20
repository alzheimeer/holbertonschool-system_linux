#include "strace.h"

/**
 * wait_syscall - Waits for syscall invocation in subprocess
 * @child: subprocess PID
 * Return: 0 if syscall is called, 0 if subprocess is terminated
*/
int wait_syscall(pid_t child)
{
	int status;

	while (1)
	{
		ptrace(PTRACE_SYSCALL, child, 0, 0);
		waitpid(child, &status, 0);
		if (WIFSTOPPED(status) && WSTOPSIG(status) & 0x80)
			return (0);
		if (WIFEXITED(status))
			break;
	}
	return (1);
}

/**
 * main - Entry point
 * @argc: Number Arguments
 * @argv: Args vector
 * @envp: Environmental variables
 * Return: failed or successful
 */
int main(int argc, char *argv[], char *envp[])
{
	pid_t child;
	int status;
	long syscall;

	if (argc < 2)
	{
		fprintf(stderr, "%s command [args...]\n", argv[0]);
		return (EXIT_FAILURE);
	}
	child = fork();
	if (child == -1)
		return (EXIT_FAILURE);
	else if (child == 0)
	{
		ptrace(PTRACE_TRACEME, 0, 0, 0), kill(getpid(), SIGSTOP);
		if (execve(argv[1], argv + 1, envp) == -1)
		{
			dprintf(STDERR_FILENO, "Exec failed: %d\n", errno);
			exit(-1);
		}
	}
	else
	{
		waitpid(child, &status, 0);
		setbuf(stdout, NULL);
		ptrace(PTRACE_SETOPTIONS, child, 0, PTRACE_O_TRACESYSGOOD);
		while (1)
		{
			if (wait_syscall(child) != 0)
				break;
			syscall = ptrace(PTRACE_PEEKUSER, child, sizeof(long) * ORIG_RAX);
			fprintf(stdout, "%s", syscalls_64_g[syscall].name);
			if (wait_syscall(child) != 0)
				break;
			fprintf(stdout, "\n");
		}
	}
	fprintf(stdout, "\n");
	return (EXIT_SUCCESS);
}
