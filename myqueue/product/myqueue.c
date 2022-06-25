#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>

#include "mystack.h"
#include "myqueue.h"

/*

Assuming the library accepts integers
*/
QueueMeta_t *myqueue_create(int item_size)
{
	QueueMeta_t *newQueue = malloc(sizeof(QueueMeta_t));
	newQueue->item_size = item_size;
	newQueue->stack_in = mystack_create(item_size);
	newQueue->stack_out = mystack_create(item_size);

	return newQueue;
}

void myqueue_delete(QueueMeta_t *queue)
{
	if (queue == NULL)
		return;
	if (queue->stack_in == NULL && queue->stack_out != NULL)
	{
		mystack_destroy(queue->stack_out);
		free(queue->stack_out);
		return;
	}
	else if (queue->stack_in != NULL && queue->stack_out == NULL)
	{
		mystack_destroy(queue->stack_in);
		free(queue->stack_in);
		return;
	}

	free(queue->stack_in);
	free(queue->stack_out);
	free(queue);
	queue->stack_in = NULL;
	queue->stack_out = NULL;
	queue = NULL;
}

int myqueue_enqueue(QueueMeta_t *que, void *obj)
{
	if (que == NULL || que->stack_in == NULL)
		return -1;
	mystack_push(que->stack_in, obj);
	return 0;
}

int myqueue_dequeue(QueueMeta_t *queue, void *obj)
{
	if (queue == NULL)
	{
		return -1;
	}
	if (queue->stack_out->stack == NULL)
	{

		while (queue->stack_in->stack != NULL)
		{
			// void *a = malloc(queue->item_size);
			mystack_pop(queue->stack_in, obj);
			mystack_push(queue->stack_out, obj);
			// free(a);
		}
	}
	void *test = malloc(sizeof(int));
	mystack_pop(queue->stack_out, obj);
	memcpy(obj, test, sizeof(test));

	return 1;
}
