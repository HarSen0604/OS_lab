#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int num;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        exit(1);
    }
    
    num = atoi(argv[1]);
    int pipefd[2];
    pid_t pid;

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(1);
    }

    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(1);
    } else if (pid == 0) {
        // Child process
        close(pipefd[1]);

        for (int i = 0; i < 5; i++) {
            pid_t pid_child = fork();

            if (pid_child == -1) {
                perror("fork");
                exit(1);
            } else if (pid_child == 0) {
                // Child of child process
                int n, result;
                read(pipefd[0], &n, sizeof(n));
                result = n / 5;

                char filename[20];
                sprintf(filename, "sample%d.txt", i+1);
                FILE *fp = fopen(filename, "w");
                if (fp == NULL) {
                    perror("fopen");
                    exit(1);
                }
                fprintf(fp, "%d", result);
                fclose(fp);
                exit(0);
            }
        }
        close(pipefd[0]);
        exit(0);
    } else {
        // Parent process
        close(pipefd[0]);

        for (int i = 0; i < 5; i++) {
            write(pipefd[1], &num, sizeof(num));
            wait(NULL);
        }
        close(pipefd[1]);
        printf("Done!\n");
        exit(0);
    }
}
