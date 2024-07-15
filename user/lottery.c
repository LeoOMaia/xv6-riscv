#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(void)
{
    int process[3], tickets[3] = {10, 20, 30};
    for (int i = 0; i < 3; i++)
    {
        process[i] = fork();
        if (process[i] == 0)
        {
            settickets(tickets[i]);
            while (1);
            printf("This should not be printed\n");
            exit(0);
        }
    }
    int time_sleep = 30;
    for (int j = 0; j < 3; j++)
    {
        sleep(time_sleep);
        struct pstat p;
        printf("Printing pstat in %d seconds\n", time_sleep);
        if(getpinfo(&p) != 0){
            printf("Error in getpinfo\n");
            exit(1);
        }

        for (int i = 0; i < NPROC; i++)
        {
            //ignoring init, sh and 3 process for our lottery
            if (p.pid[i] < 4)
                continue;
            if (p.inuse[i])
            {
                printf("pid: %d\n", p.pid[i]);
                printf("ticks: %d\n", p.ticks[i]);
                printf("tickets: %d\n", p.tickets[i]);
                printf("\n");
            }
        }
        printf("--------------------\n");
        time_sleep += 30;
    }

    for (int i = 0; i < 3; i++)
    {
        kill(process[i]);
    }
    exit(0);
}