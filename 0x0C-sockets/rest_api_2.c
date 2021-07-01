#include "rest_api.h"

/**
 * send_created - send 201 code with JSON body
 * @sck: socket fd
 * @queue: queue of todo tasks
 */
void send_created(int sck, queue_t *queue)
{
	char buf[JSON_SIZE];

	serialize(buf, JSON_SIZE, queue->last);
	dprintf(sck,
			"HTTP/1.1 201 Created\r\n"
			"Content-Length: %lu\r\nContent-Type: application/json\r\n\r\n%s",
			strlen(buf), buf);
}

/**
 * send_all_todos - send all todos as JSON
 * @sck: socketr fd
 * @queue: queue of todos
 * Return: 0 on success
 */
int send_all_todos(int sck, queue_t *queue)
{
	size_t bytes = 0, size;
	char buf[10 * BUFSIZ];
	todo_list *node;

	size = queue->size;
	node = queue->first;
	while (node)
	{
		serialize(buf + bytes, 10 * BUFSIZ - bytes, node);
		bytes += strlen(buf + bytes);
		node = node->next;
		--size;
		if (size)
		{
			*(buf + bytes) = ',';
			++bytes;
		}
	}

	dprintf(sck,
			"HTTP/1.1 200 OK\r\n"
			"Content-Length: %lu\r\nContent-Type: application/json\r\n\r\n[%s]",
			strlen(buf) + 2, buf);
	return (0);
}

/**
 * send_todo_id - handles incoming GET request with queuries
 * @sck: socket fd
 * @queue: queue of todos
 * @id: id of a task to send
 * Return: 0 on success, -1 on failure
 */
int send_todo_id(int sck, queue_t *queue, size_t id)
{
	todo_list *node;
	char buf[JSON_SIZE];

	node = find_by_id(queue, id);
	if (!node)
	{
		send_err(sck, 404);
		return (-1);
	}
	serialize(buf, JSON_SIZE, node);
	dprintf(sck,
			"HTTP/1.1 200 OK\r\n"
			"Content-Length: %lu\r\nContent-Type: application/json\r\n\r\n%s",
			strlen(buf), buf);
	return (0);
}

/**
 * handle_post_req - handles incoming POST requests
 * @sck: socket fd
 * @header: rwa HTTP response
 * @queue: queue of todos
 * Return: 0 on success, -1 on failure
 */
int handle_post_req(int sck, char *header, queue_t *queue)
{
	char *crlf = "\r\n\r\n", *content_len, *title, *desc, *body;

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
