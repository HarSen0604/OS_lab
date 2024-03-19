#include <stdio.h> //printf, fgets, perror
#include <string.h> //strcspn, strtok, strcmp
#include <unistd.h> //chdir, getcwd

int main()
{
    char display[150], input[20] = "";

    while(1)
    {
        printf("\n%s $ ", getcwd(display, 150));
        fgets(input, 20, stdin);
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

        if (strcmp("~", options[1]) == 0)
        {
            if (chdir("/Users") != 0)
            {
                perror("Failed");
            }
        }
        else if (strcmp("..", options[1]) == 0)
        {
            if (chdir("..") != 0)
            {
                perror("Failed");
            }
        }
        else
        {
            if (chdir(options[1]) != 0)
            {
                perror("Failed");
            }
        }
    }
    return 0;
}