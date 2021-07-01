#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * struct todo_list_s - todo list struct
 * @id: id of a task
 * @title: title of a task
 * @desc: description of a task
 * @next: next task
 */
typedef struct todo_list_s
{
	size_t id;
	char *title;
	char *desc;
	struct todo_list_s *next;
} todo_list;

/**
 * struct queue_s - Queue
 * @size: size of queue
 * @first: first node
 * @last: last node
 */
typedef struct queue_s
{
	int size;
	todo_list *first;
	todo_list *last;
} queue_t;

size_t print_listint(const todo_list *head);
todo_list *add_nodeint(todo_list **head, const int n);
void free_list(todo_list *head);
todo_list *get_nodeint_at_index(todo_list *head, unsigned int index);
int delete_nodeint_at_index(todo_list **head, unsigned int index);

queue_t *create_queue(void);
void en_queue(queue_t *queue, char *title, char *desc);
void free_queue(queue_t **q);
todo_list *find_by_id(queue_t *queue, size_t id);
int delete_by_id(queue_t *queue, size_t id);

#endif /* DATA_STRUCTURES_H */
