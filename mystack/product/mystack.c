
#include "mystack.h"
#include "logging.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
/* The stack is an abstract data type.
 * this means that the internal structures are
 * never exposed to the users of the library.
 */

/* Note: the stacks have no knowledge of what types
 * they are storing. This is not a concern of the stack
 */

/*
typedef struct stackObject
{
	void* obj;
	struct stackObject *next;
} StackObject_t;

typedef struct stackMeta
{
	StackObject_t *stack;
	size_t objsize;
	int numelem;
} StackMeta_t;
*/
StackObject_t *createStackObject(void *obj, size_t objsize)
{
	StackObject_t *new = malloc(sizeof(StackObject_t));
	if (new == NULL)
		return NULL;
	new->next = NULL;
	new->obj = malloc(objsize);
	memcpy(new->obj, obj, objsize);
	return new;
}
StackMeta_t *mystack_create(size_t objsize)
{
	StackMeta_t *new = malloc(sizeof(StackMeta_t));
	if (new == NULL)
		return NULL;
	new->numelem = 0;
	new->objsize = objsize;
	new->stack = NULL;
	return new;
}

int mystack_push(StackMeta_t *stack, void *obj)
{

	if (stack == NULL)
		return -1;
	// StackObject_t *temp1 = stack->stack;
	if (stack->stack == NULL) // stack is empty
	{
		stack->stack = createStackObject(obj, stack->objsize);
		stack->numelem++;
		return 0;
	}
	else
	{
		StackObject_t *temp = createStackObject(obj, stack->objsize);
		temp->next = stack->stack;
		stack->stack = temp;
		stack->numelem++;
		return 0;
	}
}

int mystack_pop(StackMeta_t *stack, void *obj)
{
	if (stack == NULL)
		return -1;
	if (stack->stack == NULL)
		return -1;
	// StackMeta_t *temp = stack;
	StackObject_t *stackToPop = stack->stack;
	memcpy(obj, stackToPop->obj, stack->objsize);
	if (stackToPop->next == NULL)
	{
		free(stackToPop->obj);
		free(stackToPop);
		stack->stack = NULL;
		return 0;
	}
	stack->stack = stackToPop->next;
	free(stackToPop->obj);
	free(stackToPop);
	stack->numelem--;
	return 0;
}

void mystack_destroy(StackMeta_t *stack)
{
	if (stack == NULL)
		return;

	else if (stack->stack != NULL)
	{
		StackObject_t *temp = stack->stack;
		StackObject_t *toDest;
		while (temp->next != NULL)
		{
			toDest = temp;
			temp = temp->next;
			free(toDest->obj);
			free(toDest);
		}
		free(temp->obj);
		free(temp);
		stack->stack = NULL;
		stack->numelem = 0;
	}
	free(stack);
}

int mystack_nofelem(StackMeta_t *stack)
{
	if (stack == NULL)
		return 0;
	if (stack->stack == NULL)
		return 0;
	int r = 0;
	StackObject_t *temp = stack->stack;
	while (temp != NULL)
	{
		temp = temp->next;
		r++;
	}
	/*	Or does this return the number from the stack itself?
	 *	then:
	 *	return stack->numelem;


	*/

	return r;
}
