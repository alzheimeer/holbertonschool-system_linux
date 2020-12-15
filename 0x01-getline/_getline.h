#ifndef INC_0X01_GETLINE_GETLINE_H
#define INC_0X01_GETLINE_GETLINE_H

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define READ_SIZE 1024

char *_getline(const int fd);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

#endif /*INC_0X01_GETLINE_GETLINE_H*/
