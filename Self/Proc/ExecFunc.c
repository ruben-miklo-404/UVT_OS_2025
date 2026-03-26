#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();
    
    if (pid < 0) {
        perror("fork failed");
        exit(1);
    } else if (pid == 0) {
        // Child process - execute ls command
        printf("Child process about to execute 'ls -l'\n");
        
        // Different ways to use exec:
        // execl("/bin/ls", "ls", "-l", NULL);
        // execlp("ls", "ls", "-l", NULL);
        
        char *args[] = {"ls", "-l", NULL};
        execvp("ls", args);
        
        // If we get here, exec failed
        perror("exec failed");
        exit(1);
    } else {
        // Parent process
        wait(NULL);
        printf("Parent: child finished execution\n");
    }
    
    return 0;
}