#include "data_structures.h"

/**
 * create_queue - Creates an empty queue
 * Return: new queue
*/
queue_t *create_queue(void)
{
	queue_t *q = malloc(sizeof(queue_t));

	if (!q)
		exit(EXIT_FAILURE);

	q->first = q->last = NULL;
	q->size = 0;

	return (q);
}

/**
 * en_queue - en_queue
 * @queue: queue
 * @title: title field
 * @desc: description field
 */
void en_queue(queue_t *queue, char *title, char *desc)
{
	todo_list *temp = malloc(sizeof(todo_list));

	if (!temp)
		exit(EXIT_FAILURE);

	temp->title = strdup(title);
	temp->desc = strdup(desc);
	temp->next = NULL;
	queue->size++;
	if (queue->last == NULL)
	{
		queue->first = queue->last = temp;
		temp->id = 0;
	}
	else
	{
		temp->id = queue->last->id + 1;
		queue->last->next = temp;
		queue->last = temp;
	}
}


/**
* free_queue - frees a queue
* @q: pointer to head of queue
* Return: Nothing.
*/
void free_queue(queue_t **q)
{
	todo_list *prev;
	todo_list *head;

	head = (*q)->first;

	while (head)
	{
		prev = head->next;
		free(head->title);
		free(head->title);
		free(head);
		head = prev;
	}

	free(*q);
	*q = NULL;
}
