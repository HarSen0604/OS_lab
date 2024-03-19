#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool isPrime(int num)
{
    for (int i = 2; i*i <= num; i++)
    {
        if (num % i == 0)
        {
            return false;
        }
    }
    return true;
}

int main(int argc, char *argv[])
{
    FILE *fp = fopen("prime.txt", "w");
    int num = atoi(argv[1]);
    for (int i = 2; i < num; i++)
    {
        if(isPrime(i))
        {
            fprintf(fp, "%d\n", i);
        }
    }
    fclose(fp);
    return 0;
}