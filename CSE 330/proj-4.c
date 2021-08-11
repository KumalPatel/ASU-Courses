#include "sem.h"

int numP, numE;

struct SemQueue* Sem;

void Philosophers(int ID)
{
    P(&Sem[(ID-1) % numP]); // access to right chopstick
    yield();
    P(&Sem[ID % numP]); // attmpts to access left chopstick
    yield();

    printf("\n Philosopher %d is eating \n", ID);

    V(&Sem[(ID-1) % numP]); // releases right chopstick
    V(&Sem[ID % numP]); // releases left chopstick

    ucontext_t* previous = &(RunQ.head->context);
    DelQueue(&RunQ);
    swapcontext(previous, &(RunQ.head->context));

}

int main()
{
    scanf("%d,%d", &numP, &numE);

    if(numP == 0)
        return 0;
    Sem = malloc(sizeof(*Sem) * numP); // creates numP instances

    for(int i = 0; i < numP; i++) // Initializes every semaphore to 1
        InitSem(&Sem[i], 1);

    InitQueue(&RunQ);
    for(int i = 0; i < numE; i++) // store ids in  runQ
    {
        int threadID;
        scanf("%d",&threadID);
        start_thread(&Philosophers, threadID);
    }
    run();


    return 0;
}