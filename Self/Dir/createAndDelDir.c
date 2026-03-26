#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    // Create a directory
    if (mkdir("test_directory", 0755) == -1) {
        perror("Error creating directory");
        exit(1);
    }
    printf("Directory created successfully\n");
    
    // Create a file in the directory
    FILE *file = fopen("test_directory/example.txt", "w");
    if (file) {
        fprintf(file, "Test file content\n");
        fclose(file);
    }
    
    // Note: rmdir only works on empty directories
    // To remove non-empty directories, you need to remove files first
    
    printf("Use 'ls test_directory' to see the created directory\n");
    return 0;
}