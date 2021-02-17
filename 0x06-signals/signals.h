#ifndef BCDBD8BA_4B9F_478C_88F8_F10E69B8F0FF
#define BCDBD8BA_4B9F_478C_88F8_F10E69B8F0FF
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#define UNUSED(x) (void)(x)


int handle_signal(void);
void (*current_handler_signal(void))(int);
int handle_sigaction(void);
void (*current_handler_sigaction(void))(int);
int trace_signal_sender(void);
int pid_exist(pid_t pid);
void all_in_one(void);
int sigset_init(sigset_t *set, int *signals);
int signals_block(int *signals);
int signals_unblock(int *signals);
int handle_pending(void (*handler)(int));


#endif /* BCDBD8BA_4B9F_478C_88F8_F10E69B8F0FF */
