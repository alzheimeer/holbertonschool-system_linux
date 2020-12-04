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

	if (argc == 1)
		basic("./", argv, 2, pila, hidden, longd);
	else
	{
		for (i = 1; i < argc; i++)
		{
			if (argv[i][0] == '-')
				cases(argv, i, &pila, &hidden, &longd);
			else
				nDir++;
		}
		if (nDir > 0)
		{
			for (i = 1; i < argc; i++)
			{
				if (nDir == 1)
				{
					if (argv[i][0] != '-')
						basic(argv[i], argv, 2, pila, hidden, longd);
				}
				else
				{
					if (argv[i][0] != '-')
					{
						printf("%s:\n", argv[i]);
						basic(argv[i], argv, 2, pila, hidden, longd);
					}
					if (i < argc - 1)
						printf("\n"), printf("\n");
				}
			}
		}
		else
			basic("./", argv, 2, pila, hidden, longd);
	}
	return (0);
}

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
 * @caseT: fsdfsdfsdf
 * @pila: flag -1
 * @hidden: flaq -a
 * @longd: flag -l
 * Return: Always 0.
 */
int basic(char *filename, char **argv, int caseT,
		  int pila, int hidden, int longd)
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
			switch (caseT)
			{
			case 1:
				break;
			case 2:
				if (hidden == 0)
					if (*read->d_name == '.')
						continue;
				if (longd == 0)
					printf("%s  ", read->d_name);
				if (longd == 1)
					ldetails(sb, read);
				if (pila == 1)
					printf("\n");
				break;
			default:
				break;
			}
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
 * Return: none
 */
void cases(char **argv, int i, int *pila, int *hidden, int *longd)
{
	if (_strcmp(argv[i], "-1") == 0)
		*pila = 1;
	else if (_strcmp(argv[i], "-a") == 0)
		*hidden = 1;
	else if (_strcmp(argv[i], "-A") == 0)
		printf("task 4: ver archivos Horizontales + Ocultos y sin . y ..\n");
	else if (_strcmp(argv[i], "-l") == 0)
		*longd = 1;
	else if (_strcmp(argv[i], "-lA") == 0 || _strcmp(argv[i], "-Al") == 0)
		printf("task 6 combina -lA -Al -la  -al \n");
	else if (_strcmp(argv[i], "-r") == 0)
		printf("task 7: reverso\n");
	else if (_strcmp(argv[i], "-S") == 0)
		printf("task 8: ordena por tamaño\n");
	else if (_strcmp(argv[i], "-t") == 0)
		printf("task 9: ordena por tiempo\n");
	else if (_strcmp(argv[i], "-R") == 0)
		printf("task 10:Recursion\n");
	else
		error_handler(argv, "./", 1);
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
