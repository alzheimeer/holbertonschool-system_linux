#include "hls.h"

/**
 * flaqs- check the code for Holberton School students.
 * @sb: number the arguments
 * @read:  fdsfsfsfs
 * @pila: flag -1
 * @longd: flag -l
 * @pila: flag -1
 * @reverse: flag -r
 * @sortsize: flag -S
 * @sorttime: flaq -t
 * @recursion: flag -R
 * Return: None.
 */
void flaqs(struct stat sb, struct dirent *read, int pila, int longd,
	int reverse, int sortsize, int sorttime, int recursion)
{
	if (longd == 0 && pila == 1)
		printf("%s", read->d_name);
	else if (longd == 0 && pila == 0)
		printf("%s  ", read->d_name);
	if (longd == 1)
		ldetails(sb, read);
	if (reverse == 1)
		printf("\n");
	if (sortsize == 1)
		printf("\n");
	if (sorttime == 1)
		printf("\n");
	if (recursion == 1)
		printf("\n");
}
/**
 * verFile- check the code for Holberton School students.
 * @argv: argv
 * @filename: argument
 * Return: None.
 */
void verFile(char **argv, char *filename)
{
	int i = 0, j = 0, x = 0;
	struct dirent *read;
	char *p[50];
	char w[50], k[50];
	DIR *dir;
	char *tokens = NULL, *token = NULL;

	token = _strtok(filename, "/");
	while (token != NULL)
	{
		p[i] = token;
		token = _strtok(NULL, "/");
		i++;	}
	sprintf(w, "%s", p[0]);
	for (j = 1; j < i - 1; j++)
		sprintf(w, "%s/%s", w, p[j]);
	tokens = w;
	if (i == 1)
	{
		sprintf(k, "./%s", filename);
		dir = opendir("./");
		sprintf(w, "%s", w);	}
	else
	{
		dir = opendir(tokens);
		filename = p[j];
		sprintf(w, "%s/%s", w, p[j]);
	}
	if (dir != NULL)
	{
		while ((read = readdir(dir)) != NULL)
		{
			if (_strcmp(filename, read->d_name) == 0)
			{
				printf("%s\n", w), x = 2;	}
		}
		if (x != 2)
			error_handler(argv, w, 0);
	}
	closedir(dir);
}
/**
 * betty- check the code for Holberton School students.
 * @i: int
 * @argc: argc
 * @nDir: flaq
 * @argv: argument
 * @pila: flaq
 * @hidden: flaq
 * @longd: flaq
 * @hidden2: dasda
 * Return: None.
 */
void betty(int i, int argc, int nDir, char **argv,
	int pila, int hidden, int longd, int hidden2)
{
	DIR *dir;
	int reverse = 0, sortsize = 0, sorttime = 0, recursion = 0;

	dir = opendir(argv[i]);
	if (nDir == 1)
	{
		if (dir != NULL)
			basic(argv[i], argv, pila, hidden, longd,
				hidden2, reverse, sortsize, sorttime, recursion);
		else
			verFile(argv, argv[i]);
	}
	else
	{
		if (dir != NULL)
		{
			printf("%s:\n", argv[i]);
			basic(argv[i], argv, pila, hidden, longd,
				hidden2, reverse, sortsize, sorttime, recursion);
		}
		else
			verFile(argv, argv[i]);
		if (i < argc - 1)
			printf("\n");
	}
}
/**
 * _strcmp - Compare two strings
 * @s1: The firts string
 * @s2: The second string
 *
 * Return: indication number
 */
int _strcmp(char *s1, char *s2)
{
	char c1, c2;

	do {
		c1 = *s1++;
		c2 = *s2++;
		if (c1 == '\0')
			return (c1 - c2);
	} while (c1 == c2);
	return (c1 - c2);
}
/**
 * _strtok - extracts tokens from strings.
 * @s: the string to be tokenized
 * @delim: the char used to determine tokens
 * Return: pointer to the first char in the token.
 */
char *_strtok(char *s, const char *delim)
{
	char *token;
	static int tok_s;
	static char *buftok;

	if (s != NULL)
	{
		buftok = s;
		tok_s = 0;
	}

	while (buftok[tok_s] == *delim && buftok[tok_s] != '\0')
		tok_s++;
	if (buftok[tok_s] != '\0')
		token = &buftok[tok_s];
	else
		return (NULL);
	while (buftok[tok_s] != '\0')
	{
		if (buftok[tok_s] == *delim)
		{
			buftok[tok_s] = '\0';
			tok_s++;
			return (token);
		}
		tok_s++;
	}
	return (token);
}
