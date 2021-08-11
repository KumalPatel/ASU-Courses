#include "sem.h"
#include <stdlib.h>

struct SemQueue Reader;
struct SemQueue Writer;

int rc, wc; // read & write counter
int rwc, wwc; // count of waiting R a& W

int readCount, writeCount;
int lineNo;
int ID;

int i = 0;

void read_F(int readerID)
{
    // Reader Entry
    if(wwc > 0 || wc > 0)
    {
        rwc++;
        P(&Reader); // block
        rwc--;
    }
    rc++;

    // enters scratchpad
    printf("\n This is the %d th reader reading value i = %d for the first time \n", readerID, i);
    yield();
    printf("\n This is the %d th reader reading value i = %d for the second time \n", readerID, i);


    // Reader Exit
    rc--;
    if(rc == 0 && wwc > 0)
        V(&Writer);

    ucontext_t* previous = &(RunQ.head->context);
    DelQueue(&RunQ);
    swapcontext(previous, &(RunQ.head->context));
}

void write_F(int writerID)
{

    // Writer Entry
    if(rc > 0 || wc > 0 || rwc > 0 || wwc > 0) // block
    {
        wwc++;
        P(&Writer);
        wwc--;
    }
    wc++;
    i++;

    // enter scratchpad
    printf("\n This is the %d th writer writing value i = %d \n", abs(writerID), i);
    yield();
    printf("\n This is the %d th writer verifying value i = %d \n", abs(writerID), i);


    // Writer Exit
    wc--;
    if(rwc > 0)
    {
        for(int j = 0; j < rwc; j++)
            V(&Reader);
    }
    else if(wwc > 0)
        V(&Writer);

    ucontext_t* previous = &(RunQ.head->context);
    DelQueue(&RunQ);
    swapcontext(previous, &(RunQ.head->context));
}

int main()
{
    scanf("%d,%d", &readCount, &writeCount);
    InitSem(&Reader, 0);
    InitSem(&Writer, 0);

    InitQueue(&RunQ);

    lineNo = readCount + writeCount;

    if(lineNo == 0)
        return 0;

    for(int i = 0; i < lineNo; i++)
    {
        scanf("%d,",&ID);

        if(ID > 0)
            start_thread(&read_F, ID);
        else if(ID < 0)
            start_thread(&write_F, ID);
    }

    run();

    return 0;
}
