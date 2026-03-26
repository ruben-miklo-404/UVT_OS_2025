#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd = open("seek_example.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Error opening file");
        exit(1);
    }
    
    // Write some data
    write(fd, "ABCDEFGHIJKLMNOPQRSTUVWXYZ", 26);
    
    // Move to position 10 from beginning
    lseek(fd, 10, SEEK_SET);
    write(fd, "123", 3); // Overwrites 'KLM'
    
    // Move 5 bytes backward from current position
    lseek(fd, -5, SEEK_CUR);
    write(fd, "456", 3); // Overwrites 'GHI'
    
    // Go to end of file
    lseek(fd, 0, SEEK_END);
    write(fd, "END", 3); // Appends at end
    
    close(fd);
    
    // Read and display the result
    fd = open("seek_example.txt", O_RDONLY);
    char buffer[50];
    int bytes = read(fd, buffer, sizeof(buffer));
    buffer[bytes] = '\0';
    printf("File content: %s\n", buffer);
    
    close(fd);
    return 0;
}