CC = gcc
CFLAGS = #-Wall -Werror -Wextra -pedantic
HEADERS = strace.h syscalls.h

strace_0: strace_0.o $(HEADERS)
	gcc $(CFLAGS) -o $@  $^


clean:
	rm *.o $(TASK_0)

check:
	betty *.c *.h