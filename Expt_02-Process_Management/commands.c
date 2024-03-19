#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

void child (char *options[])
{
    execvp(options[0], options);
}

int main()
{
    char input[15] = "";
    while(strcmp("exit", input) != 0)
    {
        system("pwd");
        printf("%c ", '$');
        fgets(input, 15, stdin);
        input[strcspn(input, "\n")] = '\0';
        char *token = strtok(input, " ");
        char *options[10];

        int i;
        for (i = 0; (token != NULL); i++)
        {
            options[i] = token;
            token = strtok(NULL, " ");
        }
        options[i] = NULL;
        
        pid_t pid = fork();

        if (pid == -1)
        {
            perror("Fork failed");
            exit(EXIT_FAILURE);
            break;
        }
        else if (pid == 0)
        {                
            child(options);
            break;
        }
        else
        {
            wait(NULL);
        }
    }
    return 0;
}