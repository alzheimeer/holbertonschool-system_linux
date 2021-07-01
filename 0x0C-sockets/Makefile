##
# Todo API using sockets
#
# @version 0.1
# Malloc implementation

CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -ggdb3

TASK0 = todo_api_0
TASK1 = todo_api_1
TASK2 = todo_api_2
TASK3 = todo_api_3
TASK4 = todo_api_4
TASK5 = todo_api_5
TASK6 = todo_api_6
TASK7 = todo_api_7

$(TASK7): $(TASK7).c rest_api.h rest_api.c rest_api_2.c queue.c list.c
	$(CC) $(CFLAGS) -o $@  $^

$(TASK6): $(TASK6).c rest_api.h rest_api.c rest_api_2.c queue.c list.c
	$(CC) $(CFLAGS) -o $@  $^

$(TASK5): $(TASK5).c rest_api.h rest_api.c rest_api_2.c queue.c list.c
	$(CC) $(CFLAGS) -o $@  $^

$(TASK4): $(TASK4).c rest_api.h rest_api.c rest_api_2.c queue.c list.c
	$(CC) $(CFLAGS) -o $@  $^

$(TASK3): $(TASK3).c rest_api.h rest_api.c
	$(CC) $(CFLAGS) -o $@  $^

$(TASK2): $(TASK2).c rest_api.h rest_api.c
	$(CC) $(CFLAGS) -o $@  $^

$(TASK1): $(TASK1).c rest_api.h rest_api.c
	$(CC) $(CFLAGS) -o $@  $^

$(TASK0): $(TASK0).c rest_api.h rest_api.c
	$(CC) $(CFLAGS) -o $@  $^

.PHONY: clean, check, run

clean:
	rm $(TASK0) $(TASK1) $(TASK2) $(TASK3) $(TASK4)

check:
	betty *.c *.h

# end
