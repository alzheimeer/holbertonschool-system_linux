#include "sockets.h"

/**
 * err_socket - pritn the error message when socket app fails
 * @msg: message to print
 * Return: nothing
 */
void err_socket(char *msg)
{
	printf("%s\n", msg);
	exit(EXIT_FAILURE);
}

/**
 * main - opens an IPv4/TCP socket, and listens to traffic on
 * port 12345 (Any address).
 * Return: 0 on success
 */
int main(void)
{
	int sockid = 0;
	struct sockaddr_in addrport;

	/*Create the file descriptor for a socket server*/
	sockid = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sockid == -1)
		err_socket("socket failed");
	/*Bind the socket with a port and an address in ipv4*/
	addrport.sin_family = AF_INET; /* Internet address family */
	addrport.sin_port = htons(PORT); /* Local port */
	addrport.sin_addr.s_addr = htonl(INADDR_ANY); /* Any incoming interface */

	

	/* Bind to the local address */
	if (bind(sockid, (struct sockaddr *) &addrport, sizeof(addrport)) < 0)
		err_socket("bind failed");
	/* Mark the socket so it will listen for incoming connections */
	if (listen(sockid, MAXPENDING) < 0)
		err_socket("listen failed");
	/*Waiting a client connection*/
	printf("Socket server listen on port %d\n", PORT);
	while (1)
		;

	return (0);
}
