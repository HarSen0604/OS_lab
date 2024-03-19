#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid = fork();
    if (pid == 0)
    {
        printf("Child: %d\n", pid);
        wait(NULL);
        printf("PID: %d, PPID: %d\n", getpid(), getppid());
    }
    else if (pid > 0)
    {
        printf("Parent: %d\n", pid);
        printf("PID: %d, PPID: %d\n", getpid(), getppid());        
    }
    else{;}
}