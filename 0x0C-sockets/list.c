#include "data_structures.h"

/**
 * find_by_id - find a todo by id
 * @queue: queue of todos
 * @id: id of a todo
 * Return: todo with matching @id or NULL
 */
todo_list *find_by_id(queue_t *queue, size_t id)
{
	todo_list *node;

	if (!queue || !queue->size)
		return (NULL);
	node = queue->first;
	while (node && node->id != id)
		node = node->next;
	return (node);
}

/**
 * delete_by_id - delete a todo by id
 * @queue: queue of todos
 * @id: id of a todo to be deleted
 * Return: 0 on success, -1 on failure
 */
int delete_by_id(queue_t *queue, size_t id)
{
	todo_list *node, *prev;

	if (!queue || !queue->size)
		return (-1);
	prev = NULL;
	node = queue->first;
	while (node && node->id != id)
	{
		prev = node;
		node = node->next;
	}
	if (!node)
		return (-1);
	queue->size -= 1;
	if (prev)
		prev->next = node->next;
	if (!prev)
	{
		queue->first = node->next;
	}
	if (!node->next)
	{
		queue->last = prev;
	}
	free(node->title);
	free(node->desc);
	free(node);
	return (0);
}
