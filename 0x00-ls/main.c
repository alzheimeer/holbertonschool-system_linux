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



int main(int argc, char **argv)
{
	struct stat sb;
	struct dirent *read;
	struct timespec ts;
	DIR *dir;
	char *filename = argv[1];
	dir = opendir(filename);
	char output[20];
	struct group *grp;
	struct passwd *pw;
	char *time;

	while ((read = readdir(dir)) != NULL)
	{

		lstat(output,&sb);
		printf("%c", (sb.st_mode & S_IFDIR) ? 'd' : '-');
		printf("%c", (sb.st_mode & S_IRUSR) ? 'r' : '-');
		printf("%c", (sb.st_mode & S_IWUSR) ? 'w' : '-');
		printf("%c", (sb.st_mode & S_IXUSR) ? 'x' : '-');
		printf("%c", (sb.st_mode & S_IRGRP) ? 'r' : '-');
		printf("%c", (sb.st_mode & S_IWGRP) ? 'w' : '-');
		printf("%c", (sb.st_mode & S_IXGRP) ? 'x' : '-');
		printf("%c", (sb.st_mode & S_IROTH) ? 'r' : '-');
		printf("%c", (sb.st_mode & S_IWOTH) ? 'w' : '-');
		printf("%c", (sb.st_mode & S_IXOTH) ? 'x' : '-');

		pw = getpwuid(sb.st_uid);
		grp = getgrgid(sb.st_gid);
		printf(" %s %s ", pw->pw_name, grp->gr_name);
		time = ctime(&(sb.st_mtime));


		snprintf(output, 20, "%s/%s",filename,read->d_name);
		printf("%ld %s %s\n", sb.st_size, time, read->d_name);




	}

	closedir(dir);
}
