CFLAGS = -Wall -Werror -Wextra -pedantic
HEADERS = strace.h syscalls.h
UTILS = utils

.PHONY: clean, check

INSTRUCCIONES:  $@:Se sustituye por el nombre del objetivo de la presente regla.
   				$^:Se sustituye por una lista separada por espacios de cada una de las dependencias de la presente regla.
				$*:Se sustituye por la raíz de un nombre de fichero.
   				$<:Se sustituye por la primera dependencia de la presente regla.
   				$?:Se sustituye por una lista separada por espacios de cada una de las dependencias de la presente regla que sean más nuevas que el objetivo de la regla.
   				$(@D):Se sustituye por la parte correspondiente al subdirectorio de la ruta del fichero correspondiente a un objetivo que se encuentre en un subdirectorio.
   				$(@F):Se sustituye por la parte correspondiente al nombre del fichero de la ruta del fichero correspondiente a un objetivo que se encuentre en un subdirectorio.


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
