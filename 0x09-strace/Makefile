CFLAGS = -Wall -Werror -Wextra -pedantic
HEADERS = strace.h syscalls.h

.PHONY: clean, check

strace_0: strace_0.o $(HEADERS)
	gcc $(CFLAGS) -o $@  $^

strace_1: strace_1.o $(HEADERS)
	gcc $(CFLAGS) -o $@  $^

strace_2: strace_2.o $(HEADERS)
	gcc $(CFLAGS) -o $@  $^

strace_3: strace_3.o $(HEADERS)
	gcc $(CFLAGS) -o $@  $^


clean:
	rm *.o strace_0 strace_1 strace_2 strace_3

check:
	betty *.c *.h
