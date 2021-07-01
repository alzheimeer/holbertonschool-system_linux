#include "rest_api.h"

/**
 * handle_delete_req - handle DELET method
 * @sck: socket fd
 * @queue: queue of todos
 * @id: id of a todo to be deleted
 * Return: 0 on success, -1 on failure
 */
int handle_delete_req(int sck, queue_t *queue, size_t id)
{
	int ret;

	ret = delete_by_id(queue, id);
	if (ret == -1)
	{
		send_err(sck, 404);
		return (-1);
	}
	dprintf(sck, "HTTP/1.1 204 No Content\r\n\r\n");
	return (0);
}

/**
 * parser - parse HTTP request
 * @header: header where queries are stored
 * @sck: socket fd
 * @queue: queue of todo tasks
 * Return: 0 on success, -1 on failure
*/
int parser(char *header, int sck, queue_t *queue)
{
	char method[FIELD_SIZE] = {0}, path[FIELD_SIZE] = {0};
	char *todos = "/todos";
	int bytes;
	size_t id;

	bytes = sscanf(header, "%s %s", method, path);
	if (bytes == EOF)
		return (-1);
	if (strncmp(path, todos, strlen(todos)))
	{
		send_err(sck, 404);
		return (-1);
	}
	if (!strcasecmp(method, "GET"))
	{
		bytes = sscanf(path, "/todos?id=%lu", &id);
		if (bytes == EOF)
			return (send_all_todos(sck, queue));
		return (send_todo_id(sck, queue, id));
	}
	if (!strcasecmp(method, "POST"))
	{
		return (handle_post_req(sck, header, queue));
	}
	if (!strcasecmp(method, "DELETE"))
	{
		bytes = sscanf(path, "/todos?id=%lu", &id);
		if (bytes == EOF)
			return (-1);
		return (handle_delete_req(sck, queue, id));
	}
	send_err(sck, 404);
	return (-1);
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
