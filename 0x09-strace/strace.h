#ifndef STRACE_H
#define STRACE_H

#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ptrace.h>
#include <sys/reg.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/user.h>
#include "syscalls.h"

char *read_string(pid_t child_pid, unsigned long addr);
void print_retval(long retval, struct user_regs_struct u_in);

#endif /* STRACE_H */
