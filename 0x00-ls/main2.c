#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <dirent.h>
#include <time.h>


int main(int argc, char **argv)
{
	struct stat sb;
	struct dirent *read;
	struct timespec ts;
	DIR *dir;
	char *filename = argv[1];
	dir = opendir(filename);
	char output[20];

	while ((read = readdir(dir)) != NULL)
	{

		snprintf(output, 20, "%s/%s",filename,read->d_name);

		lstat(output,&sb);
		printf("%s %ld\n", read->d_name, sb.st_size);


	}

	closedir(dir);
}
