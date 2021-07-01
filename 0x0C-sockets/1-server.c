#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>

#define PORT 12345

/**
	 * main - socket which accepts connections
	 * Return: 0 on success, 1 on failure
	 */
int main(void)
{
	int sck, new_sck, clt_size;
	struct sockaddr_in addr, client;

	sck = socket(AF_INET, SOCK_STREAM, 0);
	if (sck == -1)
		return (EXIT_FAILURE);

	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(PORT);

	if (bind(sck, (struct sockaddr *)&addr, sizeof(addr)) < 0)
		return (EXIT_FAILURE);
	listen(sck, 3);
	clt_size = sizeof(client);
	new_sck = accept(sck, (struct sockaddr *)&client, (socklen_t *)&clt_size);
	if (new_sck < 0)
		return (EXIT_FAILURE);

	printf("Client connected: %s\n", inet_ntoa(client.sin_addr));
	close(sck);
	close(new_sck);
	return (0);
}
