#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *thread_func(void *arg) {
    int i = 0;
    while (1) {
        printf("thread is running %d\n", i++);
        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t thread_id;
    int ret = pthread_create(&thread_id, NULL, thread_func, NULL);
    if (ret != 0) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }

    sleep(5);

    ret = pthread_cancel(thread_id);
    if (ret != 0) {
        perror("pthread_cancel");
        exit(EXIT_FAILURE);
    }

    pthread_join(thread_id, NULL);

    return 0;
}
