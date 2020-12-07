#include "hls.h"

/**
 * main - check the code for Holberton School students.
 * @argc: number the arguments
 * @argv: arguments
 * Return: Always 0.
 */
int main(int argc, char **argv)
{
	int i, nDir = 0, pila = 0, hidden = 0, longd = 0;
	int hidden2 = 0, reverse = 0, sortsize = 0, sorttime = 0, recursion = 0;

	if (argc == 1)
		basic("./", argv, pila, hidden, longd,
			hidden2, reverse, sortsize, sorttime, recursion);
	else
	{
		for (i = 1; i < argc; i++)
		{
			if (argv[i][0] == '-')
				cases(argv, i, &pila, &hidden, &longd,
					&hidden2, &reverse, &sortsize, &sorttime, &recursion);
			else
				nDir++;
		}
		if (nDir > 0)
		{
			for (i = 1; i < argc; i++)
			{
				if (argv[i][0] != '-')
					betty(i, argc, nDir, argv, pila, hidden, longd, hidden2);
			}
		}
		else
			basic("./", argv, pila, hidden, longd,
				hidden2, reverse, sortsize, sorttime, recursion);	}
	return (0);	}

/**
 * ldetails - check the code for Holberton School students.
 * @sb: number the arguments
 * @read:  fdsfsfsfs
 * Return: Always 0.
 */
int ldetails(struct stat sb, struct dirent *read)
{
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
	time[16] = '\0';
	time = time + 4;
	printf("%ld %s %s\n", sb.st_size, time, read->d_name);
	return (0);
}

/**
 * basic - check the code for Holberton School students.
 * @filename: number the arguments
 * @argv:  fdsfsfsfs
 * @pila: flag -1
 * @hidden: flaq -a
 * @longd: flag -l
 * @pila: flag -1
 * @hidden2: flaq -A
 * @reverse: flag -r
 * @sortsize: flag -S
 * @sorttime: flaq -t
 * @recursion: flag -R
 * Return: 0.
 */
int basic(char *filename, char **argv,
		  int pila, int hidden, int longd, int hidden2,
		  int reverse, int sortsize, int sorttime, int recursion)
{
	char sal[128];
	struct stat sb;
	struct dirent *read;
	DIR *dir;

	dir = opendir(filename);
	if (dir != NULL)
	{
		while ((read = readdir(dir)) != NULL)
		{
			sprintf(sal, "%s/%s", filename, read->d_name);
			if (lstat(sal, &sb) == -1)
			{
				perror("stat");
				return (errno);
			}

			if (hidden == 0 && hidden2 == 0)
			{
				if (*read->d_name == '.')
					continue;
			}
			if (hidden == 0 && hidden2 == 1)
			{
				if (_strcmp(".", read->d_name) == 0 ||
					_strcmp("..", read->d_name) == 0)
					continue;
			}
			flaqs(sb, read, pila, longd,
				reverse, sortsize, sorttime, recursion);
			if (pila == 1)
				printf("\n");
		}
	}
	else
		error_handler(argv, filename, 0);
	closedir(dir);
	return (0);
}

/**
 * cases - handles errors for hls
 * @argv: arguments
 * @i: iterable
 * @pila: flag -1
 * @hidden: flaq -a
 * @longd: flag -l
 * @hidden2: flaq -A
 * @reverse: flag -r
 * @sortsize: flag -S
 * @sorttime: flaq -t
 * @recursion: flag -R
 * Return: none
 */
void cases(char **argv, int i, int *pila, int *hidden,
	int *longd, int *hidden2, int *reverse, int *sortsize,
	int *sorttime, int *recursion)
{
	int j = 0;

	if (!argv[i][1])
		basic("-", argv, 0, 0, 0, 0, 0, 0, 0, 0);
	while (argv[i][j])
		j++;
	for (j = j - 1; j > 0; j--)
	{
		switch (argv[i][j])
			{
			case '1':
				*pila = 1;
				break;
			case 'a':
				*hidden = 1;
				break;
			case 'A':
				*hidden2 = 1;
				break;
			case 'l':
				*longd = 1;
				break;
			case 'r':
				*reverse = 1;
				break;
			case 'S':
				*sortsize = 1;
				break;
			case 't':
				*sorttime = 1;
				break;
			case 'R':
				*recursion  = 1;
				break;
			default:
				error_handler(argv, "./", 1);
				break;
			}
		}
}

/**
 * error_handler - handles errors for hls
 * @argv: arguments
 * @filename: path
 * @c: option error
 * Return: 2 for failure
 */
void error_handler(char **argv, char *filename, int c)
{
	char perr[50];

	if (c == 1)
	{
		fprintf(stderr, "hls: invalid option -- '%c'\n", argv[1][1]);
		fprintf(stderr, "Try 'hls --help' for more information.\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		if (errno == ENOENT)
			sprintf(perr, "hls: cannot access %s", filename);
		else if (errno == EACCES)
			sprintf(perr, "hls: cannot open directory %s", filename);
		perror(perr);
		exit(EXIT_FAILURE);
	}
}
