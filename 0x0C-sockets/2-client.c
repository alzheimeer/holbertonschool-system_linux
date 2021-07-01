#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
/**
	 * main - socket which connects to a server
	 * @argc: number of arguments
	 * @argv: arguments
	 * Return: 0 on success, 1 on failure
	 */
int main(int argc, char *argv[])
{
	int sck;
	struct sockaddr_in addr;
	struct hostent *host;

	if (argc < 3)
	{
		printf("Usage: %s <host> <port>\n", argv[0]);
		return (EXIT_FAILURE);
	}

	host = gethostbyname(argv[1]);
	if (!host)
		return (EXIT_FAILURE);
	sck = socket(AF_INET, SOCK_STREAM, 0);
	if (sck == -1)
		return (EXIT_FAILURE);
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(inet_ntoa(*(struct in_addr *)host->h_addr));
	addr.sin_port = htons(strtol(argv[2], NULL, 10));

	if (connect(sck, (struct sockaddr *)&addr, sizeof(addr)) < 0)
	{
		return (EXIT_FAILURE);
	}
	printf("Connected to %s:%s\n", argv[1], argv[2]);
	close(sck);
	return (0);
}
