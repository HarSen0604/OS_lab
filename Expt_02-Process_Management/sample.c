// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>

// int main()
// {
//     char *args[] = {"./even", "10", NULL};
//     execvp(args[0], args);
//     return 0;
// }

#include <stdio.h>

int main()
{
    FILE *fp = fopen("prime.txt", "r");
    int num;
    while(fscanf(fp, "%d\n", &num) == 1)
    {
        printf("%d\n", num);
    }
    fclose(fp);
}
