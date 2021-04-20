#ifndef _STRACE_H
#define _STRACE_H

#include "syscalls.h"
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

void trace_child(char **av, char **envp);
void trace_parent(pid_t child_pid);
int await_syscall(pid_t child_pid);

#endif
