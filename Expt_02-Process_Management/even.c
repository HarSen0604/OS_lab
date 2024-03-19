#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int num = atoi(argv[1]);
    for (int i = 0; i <= num; i++)
    {
        if (i % 2 == 0)
            printf("Even: %d\n", i);
    }
    char *args[] = {"./odd", "10", NULL};
    execvp(args[0], args);
    return 0;
}
