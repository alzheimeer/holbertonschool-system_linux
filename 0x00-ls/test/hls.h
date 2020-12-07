#ifndef B79F7134_C774_433E_A9D1_31DF1009321A
#define B79F7134_C774_433E_A9D1_31DF1009321A

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <dirent.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <errno.h>
#include <string.h>

void verFile(char **argv, char *filename);

int basic(char *filename, char **argv,
		  int pila, int hidden, int longd, int hidden2,
		  int reverse, int sortsize, int sorttime, int recursion);

int ldetails(struct stat sb, struct dirent *read);

void error_handler(char **argv, char *filename, int c);

void cases(char **argv, int i, int *pila, int *hidden,
	int *longd, int *hidden2, int *reverse, int *sortsize,
	int *sorttime, int *recursion);

void flaqs(struct stat sb, struct dirent *read, int pila, int longd,
	int reverse, int sortsize, int sorttime, int recursion);

void betty(int i, int argc, int nDir, char **argv,
	int pila, int hidden, int longd, int hidden2);

int _strcmp(char *s1, char *s2);

char *_strtok(char *s, const char *delim);

#endif /* B79F7134_C774_433E_A9D1_31DF1009321A */
