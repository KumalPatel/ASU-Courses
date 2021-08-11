#include "threads.h"

struct SemQueue
{
    int value;
    struct Queue queue;
};

void InitSem(struct SemQueue* S, int value)
{
    S->value = value;
    InitQueue(&(S->queue));
}

void P(struct SemQueue* S)
{
    if(S->value > 0)
    {
        S->value--;
        return;
    }
    else if(S->value <= 0)
    {
        ucontext_t* previous = &(RunQ.head->context);
        AddQueue(&(S->queue), DelQueue(&RunQ)); // adds to S, and deletes head
        swapcontext(previous, &(RunQ.head->context));

        if(RunQ.head == NULL)
            exit(0);
    }
}

void V(struct SemQueue* S)
{
    S->value++;

    if (S->queue.head != NULL)
    {
        AddQueue(&RunQ, DelQueue(&(S->queue))); // deletes process and adds it to the RunQ
    }
}