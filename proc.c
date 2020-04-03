#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pid_t p01=0;
pid_t p110=0;
pid_t p120=0;
pid_t p211=0;
pid_t p222=0;
pid_t p232=0;

int main() 
{
    pid_t ppid;
    ppid = getpid();
    p01 = ppid;
    printf("Root pid: %d\n", p01);
    printf("Parent: %d, Group: %d, Session: %d\n\n", getppid(), getgid(), getsid(getpid()) );

    p110 = fork();
    ppid = getpid();
    if(ppid!=p01) p110 = ppid;
    if(ppid==p01) 
    {
        p120 = fork();
        ppid = getpid();
        if((ppid!=p01)&&(ppid!=p110)) p120 = ppid;
    }

    if(ppid!=p01)
    {
        printf("Pid child lvl 1: %d\n", ppid);
        printf("Parent: %d, Group: %d, Session: %d\n\n", getppid(), getgid(), getsid(getpid()) );
    }

    sleep(1);

    if(ppid==p110) 
    {
        p211 = fork();
        ppid = getpid();
        if(ppid!=p110)
        {
            p211 = ppid;
            printf("Pid child lvl 2: %d\n", ppid);
            printf("Parent: %d, Group: %d, Session: %d\n\n", getppid(), getgid(), getsid(getpid()) );
        }
    }

    if(ppid==p120) 
    {
        p222 = fork();
        ppid = getpid();
        if(ppid!=p120) p222 = ppid;
        if(ppid==p120)
        {
            p232 = fork();
            ppid = getpid();
            if((ppid!=p120)&&(ppid!=p222)) p232 = ppid;
        }

        if(ppid!=p120)
        {
            printf("Pid child lvl 2: %d\n", ppid);
            printf("Parent: %d, Group: %d, Session: %d\n\n", getppid(), getgid(), getsid(getpid()) );
        }
    }

    if(ppid==p01) sleep(2);
    else sleep(1);
    printf("End process %d\n\n", getpid());
    exit(0);
}
