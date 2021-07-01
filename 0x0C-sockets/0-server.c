#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>

#define PORT 12345

/**
 * main - simple socket usage example
 * Return: 0 on success, 1 on failure
 */
int main(void)
{
	int sck;
	struct sockaddr_in addr;

	sck = socket(AF_INET, SOCK_STREAM, 0);
	if (sck == -1)
		return (EXIT_FAILURE);

	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(PORT);

	if (bind(sck, (struct sockaddr *)&addr, sizeof(addr)) < 0)
		return (EXIT_FAILURE);
	listen(sck, 3);
	while (1)
		;
	return (EXIT_SUCCESS);
}
