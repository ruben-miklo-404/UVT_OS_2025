// 1. Create a C application able to read and write to a given file. The filename and the content of that file will be given as 
// cmd-line arguments at execution.
// -The application will create a subprocess that first writes to the file the received arguments.
// -The parent process will read the written file and print the information to the STDOUT.  

// E.g: ./a.out filename Today is sunny
// Will result in both the STDOUT and file filename containing/printing Todayissunny

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char** argv)
{
    if (argc < 2) 
	{
        printf("Requires 2 arguments, file name and message!\n");
        exit(1);
    }
    int id = fork();

    if (id < 0) 
	{
        fprintf (stderr, "Error creating child!\n");
        exit(2);
    }

    if(id == 0)
    {
        int fd = open(argv[1], O_CREAT | O_WRONLY | O_TRUNC, 0660);
        if (fd < 0) 
		{
            fprintf(stderr, "Error opening file!\n");
            exit(3);
        }

        int i = 2;
        while(i < argc)
        {
            ssize_t writeMessage = write(fd, argv[i], strlen(argv[i]));
            i++;
        }
        close(fd);
    }
    else
    {
        int fd = open(argv[1], O_RDONLY);

        if (fd < 0) 
		{
            fprintf(stderr, "Error opening file!\n");
            exit(4);
        }

        ssize_t n;
        char buff[1024];

        while ((n = read(fd, buff, 20)) > 0) 
		{
            buff[n] = '\0';
            printf("%s", buff);
        }

		printf("\n");

        close(fd);
    }
}