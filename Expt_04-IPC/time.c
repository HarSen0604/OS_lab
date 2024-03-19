#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/mman.h>

#define BUF_SIZE 1024

int main(int argc, char *argv[]) {
    pid_t pid;
    char buf[BUF_SIZE];
    
    // Create a shared memory area for the start time and end time
    struct timeval *start_time = mmap(NULL, sizeof(struct timeval), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, 0, 0);
    struct timeval *end_time = mmap(NULL, sizeof(struct timeval), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, 0, 0);

    gettimeofday(start_time, NULL); // Record the start time
    // Create a pipe for passing the elapsed time from the child to the parent
    int fd[2];
    if (pipe(fd) == -1) {
        perror("pipe");
        exit(1);
    }

    pid = fork();
    if (pid == -1) 
    {
        perror("fork");
        exit(1);
    } 
    else if (pid == 0) 
    { // Child process
        close(fd[0]); // Close the read end of the pipe

        // Execute the specified command
        if (execvp(argv[1], &argv[1]) == -1) {
            perror("exec");
            exit(1);
        }
    } 
    else 
    { // Parent process
        close(fd[1]); // Close the write end of the pipe

        // Wait for the child process to complete
        wait(NULL);

        gettimeofday(end_time, NULL); // Record the end time

        // Calculate the elapsed time in microseconds
        unsigned long elapsed = (end_time->tv_usec - start_time->tv_usec);

        // Read the elapsed time from the child via the pipe
        if (read(fd[0], buf, BUF_SIZE) == -1) {
            perror("read");
            exit(1);
        }
        printf("Elapsed time: %lu microseconds\n", elapsed);
    }
    return 0;
}
