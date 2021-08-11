#include "q.h"

void printElement(struct TCB_t* element)
{
	if (element != NULL)
	{
		printf("\tadr: %p\n", element);
		printf("\tcontext:%p\n", &element->context);
		printf("\tprev:%p\n", element->prev);
		printf("\tnext:%p\n", element->next);
		printf("\n");
	}
	else if (element == NULL)
		printf("Trying to print an element that is set to NULL.\n ~ Nothing to print.\n\n");
}

void printQueue(struct Queue* queue)
{
	struct TCB_t* temp = queue->head;

	printf("Printing Queue\n");
	printf("\tcount: %d\n", queue->count);
	printf("\thead:%p\n", queue->head);
	printf("\n");

	for (int i = 0; i < queue->count; i++)
	{
		printf("%d:\t%p\n", i, temp);
		printElement(temp);
		temp = temp->next;
	}

	printf("End of Queue!\n");
}

int main()
{
	struct Queue queue;
	InitQueue(&queue);

	struct TCB_t* item = NewItem();
	struct TCB_t* element1 = NewItem();
	struct TCB_t* element2 = NewItem();
	struct TCB_t* element3 = NewItem();
	struct TCB_t* element4 = NewItem();

	// Test queue
	//printQueue(&queue);

	printf("\nADDING ELEMENT:\n");
	AddQueue(&queue, element1);
	//printQueue(&queue);

	AddQueue(&queue, element2);
	//printQueue(&queue);

	AddQueue(&queue, element3);
	//printQueue(&queue);

	AddQueue(&queue, element4);
	//printQueue(&queue);

	printf("\nDELETING ELEMENT:\n");
	item = DelQueue(&queue);
	//printQueue(&queue);

	item = DelQueue(&queue);
	//printQueue(&queue);

	item = DelQueue(&queue);
	//printQueue(&queue);

	item = DelQueue(&queue);
	//printQueue(&queue);

	printf("\nROTATING QUEUE:\n");
	AddQueue(&queue, element4);
	RotateQ(&queue);
	printQueue(&queue);

	FreeItem(element1);
	FreeItem(element2);
	FreeItem(element3);
	FreeItem(element4);

	return 0;
}