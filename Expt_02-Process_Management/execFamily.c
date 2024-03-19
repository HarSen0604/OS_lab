#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    // execl("/bin/ls", "/bin/ls", "-l", NULL);

    // execlp("ls", "ls", "-l", NULL);

    /*char *const array_command[] = {"/bin/ls", "-l", NULL};
    execv(array_command[0], array_command);*/

    /*char *const array_command[] = {"echo", "Hello World", NULL};
    execvp(array_command[0], array_command);*/

    pid_t pid = fork();
    if (pid > 0)
    {
        printf("\nParent PID: %d", getpid());
        wait(NULL);
    }
    else if (pid == 0)
    {
        printf("\nChild PID: %d\nParent PID: %d\n\n", getpid(), getppid());
    }
    else{
        perror("Failure");
    }

    return 0;
}