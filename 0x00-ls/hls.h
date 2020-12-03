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

int basic(char *filename, char **argv, int caseT);
int ldetails(struct stat sb, struct dirent *read);
void error_handler(char **argv);




#endif /* B79F7134_C774_433E_A9D1_31DF1009321A */