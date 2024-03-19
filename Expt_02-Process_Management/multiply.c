#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

int target;
int p=1;

int randrange()
{
    srand(time(0));
    return rand()%((9-2+1)+2);
}

void parent()
{
    p=p*randrange();
    printf("JOHN at %d\n",p);
    if(p>=target)
    {
        printf("JOHN WON\n");
        
        exit(EXIT_SUCCESS);
    }
}

void child()
{
    p=p*randrange();
    printf("MICHEAL at %d\n",p);
    if(p>=target)
    {
        printf("MICHAEL WON\n");
        exit(EXIT_SUCCESS);
    }
}

int main(int argc, char *argv[])
{
    pid_t pid;
    target = atoi(argv[1]);
    while(p<target)
    {
        switch(pid=fork())
        {
        case -1:
            perror("fork failed");
            exit(EXIT_FAILURE);
        case 0:
            child();
            if(p >= target)
            {
                exit(EXIT_SUCCESS);
            }
        default:
            parent();
            if(p >= target)
            {
                exit(EXIT_SUCCESS);
            }            
            wait(NULL);
        }
    }
    return 0;
}
