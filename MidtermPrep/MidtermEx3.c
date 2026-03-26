// 3. Create a C application able to behave like the cp command. Propose 2 implementations (one that is using fork/exec, 
// and the other one using folder and file-specific operations to achieve the desired behaviour).
// The application will work with 2 cmd-line arguments (which can be either files or folders).
// If both of them are files, the content of the first file will be copied to the second file (will be created if it does not exist).
// If the first argument is a file, and the other is a folder, the file will be copied inside the folder.
// If both arguments are folders, the entire folder structure will be copied (recursively) into the second cmd-line path.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <stdbool.h>

void CopyFileToDirectory(const char* const sourceFile, const char* const destinationDir)
{
    char sourcePath, destPath, readChar;

    int fd_arg1 = open(sourceFile, O_RDONLY);
    if (fd_arg1 < 0)
    {
        fprintf(stderr, "Error opening the first file! %s\n", strerror(errno));
        exit(5);
    }

    ssize_t n;  
    char buff[1024];

    while ((n = read(fd_arg1, buff, 20)) > 0) 
    {
        buff[n] = '\0';
    }
    close(fd_arg1);

    char* filepath = malloc(sizeof(sourceFile) + sizeof(destinationDir) + 2);
    strcpy(filepath, destinationDir);
    strcat(filepath, "/");
    strcat(filepath, sourceFile);

    int fd_arg2 = open(filepath, O_CREAT | O_WRONLY | O_TRUNC, 0660);
    if (fd_arg2 < 0) 
    {
        fprintf(stderr, "Error opening the second file in CopyFileToDirectory! %s\n", strerror(errno));
        exit(6);
    }

    write(fd_arg2, buff, strlen(buff));
    close(fd_arg2);
}

void CopyFileContentToFile(const char* const sourceFile, const char* const destinationFile)
{
    char sourcePath, destPath, readChar;

    int fd_arg1 = open(sourceFile, O_RDONLY);
    if (fd_arg1 < 0) 
        {
        fprintf(stderr, "Error opening the first file! %s\n", strerror(errno));
        exit(3);
    }

    ssize_t n;  
    char buff[1024];

    while ((n = read(fd_arg1, buff, 20)) > 0) 
    {
        buff[n] = '\0';
    }
    close(fd_arg1);

    int fd_arg2 = open(destinationFile, O_CREAT | O_WRONLY | O_TRUNC, 0660);
    if (fd_arg2 < 0) 
        {
            fprintf(stderr, "Error opening the second file in CopyFileContentToFile! %s\n", strerror(errno));
            exit(4);
        }

    write(fd_arg2, buff, strlen(buff));
    close(fd_arg2);
}

void CopyDirectoryRecursively(const char* const sourceDir, const char* const destinationDir)
{
    char *sysCommand = "cp -r ";

    char *sysCall = malloc(sizeof(sourceDir) + sizeof(destinationDir) + sizeof(sysCommand));

    strcpy(sysCall, sysCommand);
    strcat(sysCall, sourceDir);
    strcat(sysCall, " ");
    strcat(sysCall, destinationDir);

    system(sysCall);
}

int main(int argc, char** argv)
{
    if(argc != 3) 
	{
        fprintf(stderr, "Requires 2 arguments! 2 files or 2 directories or 1 file and 1 directory. \n");
        exit(1);
    }

    struct stat sb_arg1;
    struct stat sb_arg2;
    bool arg1_init_status = stat(argv[1], &sb_arg1);
    bool arg2_init_status = stat(argv[2], &sb_arg2);

    if (arg1_init_status)
    {
        fprintf(stderr, "Error initializing arg1 file status\n");
        exit(2);
    }

    if(arg2_init_status)
    {
        fprintf(stderr, "Error initializing arg2 file status\n");
        exit(2);
    }

    if((S_ISREG(sb_arg1.st_mode)) && (S_ISDIR(sb_arg2.st_mode)))
    {
        CopyFileToDirectory(argv[1], argv[2]);
        printf("File named %s copied into directory named %s successfully!\n", argv[1], argv[2]);
        return 0;   
    }

    if(S_ISREG(sb_arg1.st_mode))
    {
        CopyFileContentToFile(argv[1], argv[2]);
        printf("File named %s copied into file named %s successfully!\n", argv[1], argv[2]);
        return 0;
    }

    if(S_ISDIR(sb_arg1.st_mode))
    {
        CopyDirectoryRecursively(argv[1], argv[2]);
        printf("Directory named %s copied into directory named %s successfully!\n", argv[1], argv[2]);
        return 0;
    }
}