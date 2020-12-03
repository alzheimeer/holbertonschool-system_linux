#include "hls.h"

/**
 * main - check the code for Holberton School students.
 * @argc: number the arguments
 * @argv: arguments
 * Return: Always 0.
 */
int main(int argc, char **argv)
{
	char sal[50], perr[50];
	struct stat sb;
	struct dirent *read;
	DIR *dir;
	char *filename;

	if (argc == 1)
		filename = "./";
	else if (argc == 2)
		filename = argv[1];
	dir = opendir(filename);
	if (dir != NULL)
	{
		while ((read = readdir(dir)) != NULL)
		{
			snprintf(sal, 20, "%s/%s", filename, read->d_name);
			if (lstat(sal, &sb) == -1)
			{
				perror("stat");
				return (errno);
			}
			la(sb, read);
		}
	}
	else
	{
		snprintf(perr, 50, "%s: cannot access %s", argv[0], argv[1]);
		perror(perr);
		exit(EXIT_FAILURE);
	}
	closedir(dir);
	return (0);
}



/**
 * la - check the code for Holberton School students.
 * @sb: number the arguments
 * @read:  fdsfsfsfs
 * Return: Always 0.
 */
int la(struct stat sb, struct dirent *read)
{
	char buffer[200];
	char *time;
	struct group *grp;
	struct passwd *pw;

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
	printf("%ld %s %s\n", sb.st_size, time, read->d_name);
}
