#include "rest_api.h"

/**
 * print_queries - print HTTP queries
 * @header: header where queries are stored
*/
void print_queries(char *header)
{
	char *tk, *queries, *p1;
	char *delim = "?=&";

	queries = strchr(header, ' ');
	if (!queries)
		return;
	++queries;
	p1 = strchr(queries, ' ');
	if (!p1)
		return;
	*p1 = '\0';
	tk = strtok(queries, delim);
	if (!tk)
		return;
	printf("Path: %s\n", tk);
	while (1)
	{
		tk = strtok(NULL, delim);
		if (!tk)
			return;
		printf("Query: ");
		printf("\"%s\" -> ", tk);
		tk = strtok(NULL, delim);
		printf("\"%s\"\n", tk);
	}
}

/**
 * accept_connection - wait for connections from users and accept them
 * @sck: descriptor of the passive socket
 * Return: -1 if failed, 0 on success
*/
int accept_connection(int sck)
{
	int new_sck, clt_size;
	struct sockaddr_in client;
	char header[BUFSIZ] = {0};

	clt_size = sizeof(client);
	while (1)
	{
		new_sck = accept(sck, (struct sockaddr *)&client, (socklen_t *)&clt_size);
		if (new_sck < 0)
			return (-1);
		printf("Client connected: %s\n", inet_ntoa(client.sin_addr));
		if (print_raw_req(header, new_sck) == -1)
		{
			close(new_sck);
			close(sck);
			return (-1);
		}
		print_queries(header);
		dprintf(new_sck, "HTTP/1.0 200 OK\r\n\r\n");
		close(new_sck);
	}
	return (0);
}

/**
 * main - socket which accepts connections
 * Return: 0 on success, 1 on failure
 */
int main(void)
{
	int sck;

	setbuf(stdout, NULL);
	sck = init_inet_socket();
	if (sck == -1)
		return (EXIT_FAILURE);
	if (accept_connection(sck) == -1)
		return (EXIT_FAILURE);
	close(sck);
	return (EXIT_SUCCESS);
}
