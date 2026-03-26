#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

int main() {
    int fd;
    char buffer[100];
    ssize_t bytes_read, bytes_written;
    
    // Create and open a file for writing
    fd = open("example.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Error opening file for writing");
        exit(1);
    }
    
    // Write to file
    char *data = "Hello, World!\nThis is a test file.\n";
    bytes_written = write(fd, data, strlen(data));
    if (bytes_written == -1) {
        perror("Error writing to file");
        close(fd);
        exit(1);
    }
    printf("Written %zd bytes to file\n", bytes_written);
    
    close(fd);
    
    // Open the same file for reading
    fd = open("example.txt", O_RDONLY);
    if (fd == -1) {
        perror("Error opening file for reading");
        exit(1);
    }
    
    // Read from file
    bytes_read = read(fd, buffer, sizeof(buffer) - 1);
    if (bytes_read == -1) {
        perror("Error reading from file");
        close(fd);
        exit(1);
    }
    
    buffer[bytes_read] = '\0'; // Null-terminate the string
    printf("Read %zd bytes from file:\n%s", bytes_read, buffer);
    
    close(fd);
    return 0;
}