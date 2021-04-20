CFLAGS = -Wall -Werror -Wextra -pedantic
HEADERS = strace.h syscalls.h
UTILS = utils

.PHONY: clean, check

strace_0: strace_0.o $(HEADERS)
	gcc $(CFLAGS) -o $@  $^

strace_1: strace_1.o $(HEADERS)
	gcc $(CFLAGS) -o $@  $^

strace_2: strace_2.o $(HEADERS)
	gcc $(CFLAGS) -o $@  $^

strace_3: strace_3.o $(HEADERS)
	gcc $(CFLAGS) -o $@  $^

strace_4: strace_4.o $(UTILS).o $(HEADERS)
	gcc $(CFLAGS) -o $@  $^

strace_5: strace_5.o $(UTILS).o $(HEADERS)
	gcc $(CFLAGS) -o $@  $^

strace_6: strace_6.o $(UTILS).o $(HEADERS)
	gcc $(CFLAGS) -o $@  $^

# strace_7: strace_7.o $(UTILS).o $(HEADERS)
# 	gcc $(CFLAGS) -o 

# strace_8: strace_8.o $(UTILS).o $(HEADERS)
# 	gcc $(CFLAGS) -o 

clean:
	rm *.o strace_0 strace_1 strace_2 strace_3 strace_4 strace_5 strace_6 strace_7 strace_8

check:
	betty *.c *.h
