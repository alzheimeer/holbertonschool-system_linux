#include "hls.h"

/**
 * flaqs- check the code for Holberton School students.
 * @sb: number the arguments
 * @read:  fdsfsfsfs
 * @pila: flag -1
 * @longd: flag -l
 * @pila: flag -1
 * @hidden2: flaq -A
 * @reverse: flag -r
 * @sortsize: flag -S
 * @sorttime: flaq -t
 * @recursion: flag -R
 * Return: None.
 */
void flaqs(struct stat sb, struct dirent *read, int pila, int longd,
	int hidden2, int reverse, int sortsize, int sorttime, int recursion)
{
	if (longd == 0 && pila == 1)
		printf("%s", read->d_name);
	else if (longd == 0 && pila == 0)
		printf("%s  ", read->d_name);
	if (longd == 1)
		ldetails(sb, read);
	if (pila == 1)
		printf("\n");
	if (hidden2 == 1)
		printf("\n");
	if (reverse == 1)
		printf("\n");
	if (sortsize == 1)
		printf("\n");
	if (sorttime == 1)
		printf("\n");
	if (recursion == 1)
		printf("\n");
}
