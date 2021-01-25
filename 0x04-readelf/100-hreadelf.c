#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/**
 * main - read elf file
 * @argc: the count of args
 * @argv: the args
 * Return: -1 in fail and 0 in success
 */
int main(int argc, char **argv)
{
	FILE *fp;
	size_t n = 0;
	char *line;
	char args[100];

	sprintf(args, "/usr/bin/readelf -W -s %s", argv[1]);
	(void)argc;
	fp = popen(args, "r");
	if (fp == NULL)
	{
		perror("popen");
		return (EXIT_FAILURE);
	}
	while (getline(&line, &n, fp) != -1)
		printf("%s", line);
	pclose(fp);
	return (EXIT_SUCCESS);
}
