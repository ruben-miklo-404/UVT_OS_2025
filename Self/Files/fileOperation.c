#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *file;
    char buffer[100];
    
    // Writing with fprintf and fwrite
    file = fopen("library_example.txt", "w");
    if (file == NULL) {
        perror("Error opening file for writing");
        exit(1);
    }
    
    fprintf(file, "This is a line written with fprintf\n");
    
    char data[] = "This is binary data written with fwrite\n";
    fwrite(data, sizeof(char), strlen(data), file);
    
    fclose(file);
    
    // Reading with fscanf and fread
    file = fopen("library_example.txt", "r");
    if (file == NULL) {
        perror("Error opening file for reading");
        exit(1);
    }
    
    // Read first line with fscanf
    fscanf(file, "%[^\n]\n", buffer);
    printf("First line: %s\n", buffer);
    
    // Read rest with fread
    size_t bytes = fread(buffer, 1, sizeof(buffer) - 1, file);
    buffer[bytes] = '\0';
    printf("Remaining content: %s", buffer);
    
    fclose(file);
    return 0;
}