#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


/**
 * main - entry
 * @argc: args count
 * @argv: args
 * @env: enviroment
 * Return: exit or fail
 */
int main(int argc, char **argv, char **env)
{
	char *comm[] = {"./hobjdump", "-sf", "", NULL};

	(void)argc;

	comm[2] = argv[1];
	if (execve("/usr/bin/objdump", comm, env) == -1)
	{
		perror("execv");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
