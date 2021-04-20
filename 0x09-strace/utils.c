#include "strace.h"

/**
 * read_string - Returns the string stored in the memory @addr
 * @child_pid: pid of the process
 * @addr: address to be looked in
 * Return: string stored in memory
 */
char *read_string(pid_t child_pid, unsigned long addr)
{
	char *str = malloc(4096);
	unsigned int allocated = 4096;
	unsigned long read = 0;
	unsigned long tmp;

	while (1)
	{
		if (read + sizeof(tmp) > allocated)
		{
			allocated *= 2;
			str = realloc(str, allocated);
		}
		tmp = ptrace(PTRACE_PEEKDATA, child_pid, addr + read);
		if (errno != 0)
		{
			str[read] = 0;
			break;
		}
		memcpy(str + read, &tmp, sizeof(tmp));
		if (memchr(&tmp, 0, sizeof(tmp)) != NULL)
			break;
		read += sizeof(tmp);
	}
	return (str);
}

/**
 * print_retval - print arguments to syscalls
 * @retval: return value of a syscall
 * @u_in: registers struct
 */
void print_retval(long retval, struct user_regs_struct u_in)
{
	char *str = ") = ";

	if (syscalls_64_g[u_in.orig_rax].ret == INT)
		fprintf(stdout, "%s%d\n", str, (int)retval);
	else if (syscalls_64_g[u_in.orig_rax].ret == LONG)
		fprintf(stdout, "%s%ld\n", str, (long)retval);
	else if (syscalls_64_g[u_in.orig_rax].ret == SIZE_T)
		fprintf(stdout, "%s%lu\n", str, (ulong)retval);
	else if (syscalls_64_g[u_in.orig_rax].ret == SSIZE_T)
		fprintf(stdout, "%s%ld\n", str, (long)retval);
	else if (syscalls_64_g[u_in.orig_rax].ret == U64)
		fprintf(stdout, "%s%lu\n", str, (ulong)retval);
	else if (syscalls_64_g[u_in.orig_rax].ret == UINT32_T)
		fprintf(stdout, "%s%lu\n", str, (ulong)retval);
	else if (syscalls_64_g[u_in.orig_rax].ret == UNSIGNED_INT)
		fprintf(stdout, "%s%u\n", str, (uint)retval);
	else if (syscalls_64_g[u_in.orig_rax].ret == UNSIGNED_LONG)
		fprintf(stdout, "%s%lu\n", str, (ulong)retval);
	else if (syscalls_64_g[u_in.orig_rax].ret == PID_T)
		fprintf(stdout, "%s%d\n", str, (int)retval);
	else
		fprintf(stdout, "%s%#lx\n", str, retval);
}
