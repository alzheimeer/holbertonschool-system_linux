#include "rest_api.h"

/**
 * init_inet_socket - initialize socket, broadcast to all (INADDR_ANY)
 * use port PORT macro
 * Return: -1 if failed, socket descriptor
*/
int init_inet_socket(void)
{
	int sck, yes = 1;
	struct sockaddr_in addr;

	sck = socket(AF_INET, SOCK_STREAM, 0);
	if (sck == -1)
		return (-1);
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(PORT);
	if (bind(sck, (struct sockaddr *)&addr, sizeof(addr)) < 0)
	{
		perror("bind");
		return (-1);
	}
	listen(sck, BACKLOG);
	if (setsockopt(sck, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1)
	{
		perror("setsockopt");
		return (-1);
	}
	printf("Server listening on port %d\n", PORT);
	return (sck);
}

/**
 * print_raw_req - print raw HTTP/1.1 request from a user
 * @header: header buffer, where HTTP header info will be stored
 * @sck: socket file descriptor
 * Return: -1 if failed, 0 on success
*/
int print_raw_req(char *header, int sck)
{
	int bytes;
	char buf[BUFSIZ] = {0};

	bytes = recv(sck, header, BUFSIZ, 0);
	if (bytes == -1)
		return (-1);
	printf("Raw request: \"%s", header);
	if (bytes == BUFSIZ)
	{
		while ((bytes = recv(sck, buf, BUFSIZ, 0)) > 0)
		{
			printf("%s", buf);
			memset(buf, 0, BUFSIZ);
		}
		if (bytes == -1)
			return (-1);
	}
	printf("\"\n");
	return (0);
}

/**
 * send_err - send error to the client
 * @sck: socket fd
 * @err_code: err_code to send to the user
 */
void send_err(int sck, int err_code)
{
	if (err_code == 411)
	{
		dprintf(sck, "HTTP/1.1 411 Length Required\r\n\r\n");
		printf("[HTTP/1.1 411 Length Required]\n");
	}
	else if (err_code == 422)
	{
		dprintf(sck, "HTTP/1.1 422 Unprocessable Entity\r\n\r\n");
		printf("[HTTP/1.1 422 Unprocessable Entity]\n");
	}
	else if (err_code == 404)
	{
		dprintf(sck, "HTTP/1.1 404 Not Found\r\n\r\n");
		printf("[HTTP/1.1 404 Not Found]\n");
	}
}

/**
 * get_queries - extract two queries, title and description
 * @sck: socket fd
 * @body: body of HTTP
 * @title: value of title query
 * @desc: value of title description query
 * Return: 0 on success, -1 on failure
 */
int get_queries(int sck, char *body, char **title, char **desc)
{
	char *title_str = "title=", *desc_str = "description=", *zero_byte;

	*title = strstr(body, title_str);
	if (!*title)
	{
		send_err(sck, 422);
		return (-1);
	}
	*title += strlen(title_str);
	*desc = strstr(body, desc_str);
	if (!*desc)
	{
		send_err(sck, 422);
		return (-1);
	}
	*desc += strlen(desc_str);
	zero_byte = strchr(*title, '&');
	if (zero_byte)
		*zero_byte = '\0';
	zero_byte = strchr(*desc, '&');
	if (zero_byte)
		*zero_byte = '\0';
	return (0);
}

/**
 * serialize -  converts todo_list entry to JSON
 * @buf: buffer where JSON will be written
 * @size: size of @buf
 * @node: node to serialize
 */
void serialize(char *buf, size_t size, todo_list *node)
{
	memset(buf, 0, size);
	sprintf(buf, "{\"id\":%lu,\"title\":\"%s\",\"description\":\"%s\"}",
			node->id, node->title, node->desc);
}
