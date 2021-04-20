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
 * print_register - print registers (params of syscalls)
 * @u_in: registers struct
 * @idx: parameter index
 * @reg: register
 * @str: delimeter
*/
void print_register(struct user_regs_struct u_in,
					int idx, ulong reg, char *str)
{
	if (syscalls_64_g[u_in.orig_rax].params[idx] != (type_t)-1 &&
		syscalls_64_g[u_in.orig_rax].params[idx] != VOID)
	{
		if (syscalls_64_g[u_in.orig_rax].params[idx] == VARARGS)
			fprintf(stdout, "%s...", str);
		else
			fprintf(stdout, "%s%#lx", str, reg);
	}
}

/**
 * print_args - print arguments to syscalls
 * @u_in: registers struct
*/
void print_args(struct user_regs_struct u_in)
{
	print_register(u_in, 0, u_in.rdi, "");
	print_register(u_in, 1, u_in.rsi, ", ");
	print_register(u_in, 2, u_in.rdx, ", ");
	print_register(u_in, 3, u_in.r10, ", ");
	print_register(u_in, 4, u_in.r8, ", ");
	print_register(u_in, 5, u_in.r9, ", ");
}

/**
 * tracer - tracer process
 * @child: subprocess PID
 * Return: EXIT_SUCCESS on success
 */
int tracer(pid_t child)
{
	int status;
	struct user_regs_struct u_in;

	waitpid(child, &status, 0);
	ptrace(PTRACE_SETOPTIONS, child, 0, PTRACE_O_TRACESYSGOOD);
	if (wait_syscall(child) != 0)
		return (EXIT_SUCCESS);
	ptrace(PTRACE_GETREGS, child, 0, &u_in);
	if (wait_syscall(child) != 0)
		return (EXIT_SUCCESS);
	ptrace(PTRACE_GETREGS, child, 0, &u_in);
	fprintf(stdout, " = %#lx\n", (ulong)u_in.rax);
	while (1)
	{
		if (wait_syscall(child) != 0)
			break;
		ptrace(PTRACE_GETREGS, child, 0, &u_in);
		fprintf(stdout, "%s(", syscalls_64_g[u_in.orig_rax].name);
		print_args(u_in);
		if (wait_syscall(child) != 0)
			break;
		ptrace(PTRACE_GETREGS, child, 0, &u_in);
		fprintf(stdout, ") = %#lx\n", (ulong)u_in.rax);
	}
	fprintf(stdout, ") = ?\n");
	return (EXIT_SUCCESS);
}

/**
 * main - Entry point
 * @argc: Args count
 * @argv: Args vector
 * @envp: Environmental variables
 * Return: EXIT_FAILURE if failed, EXIT_SUCCESS if successful
 */
int main(int argc, char *argv[], char *envp[])
{
	pid_t child;

	if (argc < 2)
	{
		fprintf(stderr, "%s command [args...]\n", argv[0]);
		return (EXIT_FAILURE);
	}

	child = fork();
	++argv;
	if (child == 0)
	{
		ptrace(PTRACE_TRACEME);
		kill(getpid(), SIGSTOP);
		return (execve(argv[0], argv, envp));
	}
	else
	{
		setbuf(stdout, NULL);
		fprintf(stdout, "execve(%p, %p, %p)", (void *)argv[0],
				(void *)argv, (void *)envp);
		return (tracer(child));
	}
}
