#include "q.h"

struct Queue RunQ;

void start_thread(void(*function), int arg)
{
	int stack_size = 8192;
	void* stackP = malloc(stack_size); // allocate memory of stack
	struct TCB_t* tcb = (struct TCB_t*)malloc(sizeof(struct TCB_t)); // allocate memory of tcb
	init_TCB(tcb, function, stackP, stack_size, arg); // intializes a TCB for a new thread
	AddQueue(&RunQ, tcb); // adds a queue tcb to the queue RunQ
}

void run()
{
	// real code
	ucontext_t parent; // get a place to store the main context, for faking
	getcontext(&parent); // magic source
	swapcontext(&parent, &(RunQ.head->context)); // start the first thread
}

void yield()
{
	RotateQ(&RunQ); // rotate runQ
	swapcontext(&(RunQ.head->prev->context), &(RunQ.head->context)); // swaps context of previous to current thread
}
