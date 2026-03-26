#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

int main()
{
    if(mkdir("files", 0755) == -1)
    {
        perror("Error creating the directory!\n");
    }

    printf("The directory has been created successfully.\n");

    FILE *file1 = fopen("files/text1.txt", "w");
    if(file1)
    {
        fprintf(file1, "Text1 content is just a test\n");
        fclose(file1);
    }

    FILE *file2 = fopen("files/text2.txt", "w");
    if(file2)
    {
        fprintf(file2, "Text2 content is also just a test\n");
        fclose(file2);
    }

    printf("Check the directory by typing in the terminal 'ls files'\n");
    return 0;
}