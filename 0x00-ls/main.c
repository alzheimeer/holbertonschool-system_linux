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


int main(int argc, char **argv)
{
	char buffer[200];
	char sal[200];
	struct stat sb;
	struct dirent *read;
	struct group *grp;
	struct passwd *pw;
	struct tm *mtm;
	DIR *dir;
	char *filename = argv[1];
	dir = opendir(filename);

	

	if (argc != 2) {
        perror("Usage: <pathname>\n");
        exit(EXIT_FAILURE);
    }

	while ((read = readdir(dir)) != NULL)
	{
		snprintf(sal, 20, "%s/%s",filename,read->d_name);
		if(lstat(sal, &sb) == -1) {
    		perror("stat");
    		return errno;
		}
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

		mtm = localtime(&sb.st_mtime);
		strftime(buffer, sizeof(buffer), "%H:%M", mtm);
		printf("%ld %s %s\n", sb.st_size, buffer, read->d_name);
	}

	closedir(dir);
	return(0);
}
