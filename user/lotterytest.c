#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"
#include "kernel/pstat.h"

void printpinfo(int pid)
{
    struct pstat pi = {0};
    getpinfo(&pi);
    int i;
    for (i = 0; i < NPROC; i++) {
        if (pi.pid[i] == pid) {
            printf("Number of tickets that PID %d has: %d\n", pid, pi.tickets[i]);
            printf("Number of ticks that PID %d has: %d\n", pid, pi.ticks[i]);
            printf("Is the process with PID %d in use? (0 or 1): %d\n\n\n", pid, pi.inuse[i]);
            break;
        }
    }
}

int main(int argc, char *argv[])
{
    int pid1, pid2, pid3;

    settickets(960); 

    sleep(1);
    // Create different processes with 10, 20 and 30 tickets
    if ((pid1 = fork()) == 0) {
        settickets(10);
        sleep(2); // Ensure this process starts last
        int pp1 = getpid();
        printf("Process started with PID %d\n", pp1);
        printf("Process with PID %d finished!\n", pp1);
        printpinfo(pp1);
        exit(0); 
    } else if ((pid2 = fork()) == 0) {
        settickets(20);
        sleep(1); // Ensure this process starts second
        int pp2 = getpid();
        printf("Process started with PID %d\n", pp2);
        printf("Process with PID %d finished!\n", pp2);
        printpinfo(pp2);
        exit(0);
    } else if ((pid3 = fork()) == 0) {
        settickets(30);
        int pp3 = getpid();
        printf("Process started with PID %d\n", pp3);
        printf("Process with PID %d finished!\n", pp3);
        printpinfo(pp3);
        exit(0);
    }

    int status;
    while (wait(&status) > 0); // Wait for all children to finish

    printpinfo(pid1);
    printpinfo(pid2);
    printpinfo(pid3);

    exit(0);
}
