#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

void list_directory(const char *path) {
    DIR *dir;
    struct dirent *entry;
    struct stat file_stat;
    char full_path[1024];
    
    dir = opendir(path);
    if (dir == NULL) {
        perror("Error opening directory");
        return;
    }
    
    printf("Contents of directory '%s':\n", path);
    printf("%-20s %-10s %s\n", "Name", "Size", "Type");
    printf("----------------------------------------\n");
    
    while ((entry = readdir(dir)) != NULL) {
        // Skip . and .. entries
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;
        
        // Build full path for stat
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
        
        if (stat(full_path, &file_stat) == -1) {
            perror("Error getting file status");
            continue;
        }
        
        // Determine file type
        const char *type;
        if (S_ISREG(file_stat.st_mode))
            type = "File";
        else if (S_ISDIR(file_stat.st_mode))
            type = "Directory";
        else if (S_ISLNK(file_stat.st_mode))
            type = "Link";
        else
            type = "Other";
        
        printf("%-20s %-10ld %s\n", entry->d_name, file_stat.st_size, type);
    }
    
    closedir(dir);
}

int main() {
    list_directory("."); // Current directory
    return 0;
}