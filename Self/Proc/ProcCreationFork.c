#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    int status;
    
    printf("Parent process started (PID: %d)\n", getpid());
    
    pid = fork();
    
    if (pid < 0) {
        // Error occurred
        perror("fork failed");
        exit(1);
    } else if (pid == 0) {
        // Child process
        printf("Child process (PID: %d, Parent PID: %d)\n", 
               getpid(), getppid());
        sleep(2); // Simulate some work
        printf("Child process exiting\n");
        exit(42); // Exit with status 42
    } else {
        // Parent process
        printf("Parent created child with PID: %d\n", pid);
        
        // Wait for child to complete
        wait(&status);
        
        if (WIFEXITED(status)) {
            printf("Child exited with status: %d\n", WEXITSTATUS(status));
        }
        printf("Parent process exiting\n");
    }
    
    return 0;
}