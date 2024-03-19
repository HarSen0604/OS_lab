#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t sem;

#define MAX 100

int fib[MAX];
int n;

void *fibonacci(void *arg)
{
    sem_wait(&sem);
    int i;
    int *n = (int *) arg;

    fib[0] = 0;
    fib[1] = 1;

    for (i = 2; i < *n; i++)
    {
        fib[i] = fib[i-1] + fib[i-2];
    }
    sem_post(&sem);

    pthread_exit(NULL);
}

int main()
{
    pthread_t tid;
    int i;
    sem_init(&sem, 0, 1);

    printf("Enter the number of Fibonacci numbers to generate: ");
    scanf("%d", &n);
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_create(&tid, &attr, fibonacci, &n);
    pthread_join(tid, NULL);
    
    for (i = 0; i < n; i++)
    {
        printf("%d ", fib[i]);
    }
    sem_destroy(&sem);
    pthread_attr_destroy(&attr);
    return 0;
}
