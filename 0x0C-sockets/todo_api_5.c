#include "rest_api.h"

/**
 * parser - parse HTTP request
 * @header: header where queries are stored
 * @sck: socket fd
 * @queue: queue of todo tasks
 * Return: 0 on success, -1 on failure
*/
int parser(char *header, int sck, queue_t *queue)
{
	char method[FIELD_SIZE] = {0}, path[FIELD_SIZE] = {0}, *body;
	char *crlf = "\r\n\r\n", *content_len, *title, *desc;
	int bytes;

	bytes = sscanf(header, "%s %s", method, path);
	if (!strcasecmp(method, "GET") && !strcmp(path, "/todos"))
		return (send_all_todos(sck, queue));
	if (strcasecmp(method, "POST") || bytes == EOF)
	{
		send_err(sck, 404);
		return (-1);
	}
	if (strcmp(path, "/todos"))
	{
		send_err(sck, 404);
		return (-1);
	}
	body = strstr(header, crlf);
	*body = '\0', body += strlen(crlf);
	content_len = strstr(header, "Content-Length");
	if (!content_len)
	{
		send_err(sck, 411);
		return (-1);
	}
	if (get_queries(sck, body, &title, &desc) == -1)
		return (-1);
	en_queue(queue, title, desc);
	send_created(sck, queue);
	return (0);
}

/**
 * accept_connection - wait for connections from users and accept them
 * @sck: descriptor of the passive socket
 * @queue: queue of todo tasks
 * Return: -1 if failed, 0 on success
*/
int accept_connection(int sck, queue_t *queue)
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
		parser(header, new_sck, queue);
		close(new_sck);
	}
	return (0);
}

/**
 * main - todo REST API
 * Return: 0 on success, 1 on failure
 */
int main(void)
{
	int sck;
	queue_t *queue;

	queue = create_queue();
	if (!queue)
		return (EXIT_FAILURE);
	setbuf(stdout, NULL);
	sck = init_inet_socket();
	if (sck == -1)
		return (EXIT_FAILURE);
	if (accept_connection(sck, queue) == -1)
		return (EXIT_FAILURE);
	close(sck);
	free_queue(&queue);
	return (EXIT_SUCCESS);
}
