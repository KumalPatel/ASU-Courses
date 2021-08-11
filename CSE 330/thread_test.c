/*
Name: Kumal Patel
ASUID: 1208493243
*/
#include "threads.h"

int global_count = 0;
int thread_count, function_count;

void funct(int threadID)
{
    int local_count = 1;
    int temp = 0;
    while (temp < function_count)
    {
        global_count = global_count + threadID;
        printf("\nThis is %d th execution of thread %d with global var value %d\n", local_count, threadID, global_count);
        temp++;
        local_count++;
        yield();
    }
}

int main()
{
    scanf("%d, %d", &thread_count, &function_count);
    InitQueue(&RunQ);

    if (thread_count == 0)
        printf("No Threads");
    else
    {
        for (int i = 1; i <= thread_count; i++)
            start_thread(funct, i);
    }

    run();
    return 0;
}