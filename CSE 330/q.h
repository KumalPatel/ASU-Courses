#include <stdio.h>
#include <stdlib.h>

#include "tcb.h"

struct qElement
{
    struct qElement* prev; // points to the prev element in the queue
    struct qElement* next; // points to the next element in the queue
    int payload;
};

struct Queue
{
    struct TCB_t* head; // pointer for first element in the queue, where TCB_t is a structure that holds the data structure of the Queue
};

struct TCB_t* NewItem()
{
    struct TCB_t* item = (struct TCB_t*)malloc(sizeof(struct TCB_t));
    return item;
}

void InitQueue(struct Queue* list) // &head = pointer to struct Queue
{
    // initalize Queue
    list->head = NULL;
}

void AddQueue(struct Queue* list, struct TCB_t* item)
{
    // check if list is empty
    if (list->head == NULL)
    {
        list->head = item;
        list->head->prev = item;
        list->head->next = item;
    }
    else // add item to tail of queue
    {
        struct TCB_t* tail = list->head->prev;

        item->next = list->head;
        item->prev = tail;
        list->head->prev = item;
        tail->next = item;
    }
}

struct TCB_t* DelQueue(struct Queue* list)
{
    struct TCB_t* temp = list->head;

   if(list->head == NULL) // if empty
       return NULL;
   else if(list->head == list->head->next) // if one item
   {
       list->head = NULL;
       return temp;
   }
   else
   {
       list->head = list->head->next;
       list->head->prev = list->head->prev->prev;
       list->head->prev->next = list->head;
       return temp;
   }
}

void RotateQ(struct Queue* list)
{
    AddQueue(list, DelQueue(list));
}
