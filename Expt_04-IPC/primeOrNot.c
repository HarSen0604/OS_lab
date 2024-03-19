#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

void *prime(int num)
{
    bool value = false;
    for (int j = 2; j <= num; j++)
    {
        value = false;
        for (int i = 2; i*i <= j; i++)
        {
            if (j % i == 0)
            {
                value = true;
                break;
            }
        }
        (!value) ? printf("%d\n", j) : printf("");
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    int num = atoi(argv[1]);

    pthread_t t1;
    pthread_create(&t1, NULL, prime, num);
    pthread_join(t1, NULL);
    return 0;
}