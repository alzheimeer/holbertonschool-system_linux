#include "hls.h"

/**
 * main - check the code for Holberton School students.
 * @argc: number the arguments
 * @argv: arguments
 * Return: Always 0.
 */
int main(int argc, char **argv)
{
	char *filename;
	int i, nDir = 0;
	

	if (argc == 1)
		basic("./", *argv, 2);
	else
	{
		for(i = 1; i < argc; i++)
		{
			if(argv[i][0] == '-')
			{
				if (strcmp(argv[i], "-1") == 0) 
				{
					basic("./", *argv, 3);
				} 
				else if (strcmp(argv[i], "-a") == 0)
				{
					printf("task 3: ver archivos Horizontales + Ocultos\n");
				}
				else if (strcmp(argv[i], "-A") == 0)
				{
					printf("task 4\n");
				}
				else if (strcmp(argv[i], "-l") == 0)
				{
					printf("task 5\n");
				}
				else if (strcmp(argv[i], "-lA") == 0)
				{
					printf("task 6 combina -lA -Al -la  -al \n");
				}
				else if (strcmp(argv[i], "-r") == 0)
				{
					printf("task 7\n");
				}
				else if (strcmp(argv[i], "-S") == 0)
				{
					printf("task 8\n");
				}
				else if (strcmp(argv[i], "-t") == 0)
				{
					printf("task 9\n");
				}
				else if (strcmp(argv[i], "-R") == 0)
				{
					printf("task 10\n");
				}
				else 
				{
					printf("Opcion Erronea\n");
				}
			}
			else
				nDir++;
		
			if (argc == 2)
				filename = argv[1];
		
		}
		if (nDir == 1)
			basic(argv[1], *argv, 2);
	}
		
	
	return (0);
}



/**
 * la - check the code for Holberton School students.
 * @sb: number the arguments
 * @read:  fdsfsfsfs
 * Return: Always 0.
 */
int ldetails(struct stat sb, struct dirent *read)
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

/**
 * basic - check the code for Holberton School students.
 * @sb: number the arguments
 * @read:  fdsfsfsfs
 * Return: Always 0.
 */
int basic(char *filename, char **argv, int caseT)
{
	
	char sal[50], perr[50];
	struct stat sb;
	struct dirent *read;
	DIR *dir;
	

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
			switch (caseT)
			{
			  case 1:
					ldetails(sb, read);
				break;
			  case 2:
			  		if (*read->d_name == '.')
						continue;
					printf("%s ", read->d_name);
				break;
			  case 3:
			  		if (*read->d_name == '.')
						continue;
					printf("%s\n", read->d_name);
				break;

			  default:
				break;
			}
		}
	}
	else
	{
		snprintf(perr, 50, "%s: cannot access %s", argv[0], argv[1]);
		perror(perr);
		exit(EXIT_FAILURE);
	}
	closedir(dir);
	return(0);
}
