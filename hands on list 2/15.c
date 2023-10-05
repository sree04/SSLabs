//15. Write a simple program to send some data from parent to the child process

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
    int pipe_fd[2]; 
    pid_t child_pid;
    char message[] = "Write here"; 
    // Create a pipe
    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    child_pid = fork();
    if (child_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (child_pid == 0) { 
        close(pipe_fd[1]); 
        char buffer[256];
        ssize_t num_bytes = read(pipe_fd[0], buffer, sizeof(buffer));
        if (num_bytes == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }
        printf("Child received: %s\n", buffer);
        close(pipe_fd[0]); 
    } else { 
        close(pipe_fd[0]); 
        ssize_t num_bytes = write(pipe_fd[1], message, strlen(message));
        if (num_bytes == -1) {
            perror("write");
            exit(EXIT_FAILURE);
        }
        close(pipe_fd[1]); 
    }
    return 0;
}
