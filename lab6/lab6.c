#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char** argv) 
{
    if (argc <= 2) 
	{
        printf("Requires 2 arguments, file name and message!");
        exit(1);
    }
    int id = fork();

    if (id < 0) 
	{
        fprintf (stderr, "Error creating child!");
        exit(2);
    }

    if (id == 0) 
	{  
		// child
        // open file and write
        int fd = open(argv[1] , O_WRONLY | O_TRUNC);
        if (fd < 0) 
		{
            fprintf(stderr, "Error opening file!");
            exit(3);
        }

        int i = 2;

        while (i < argc) 
		{
            ssize_t writeMessage = write(fd, argv[i], strlen(argv[i]));
            i++;
        }
        close(fd);
    }

    else 
	{
        // parent
        int status;
        wait(&status);
        int fd = open(argv[1] , O_RDONLY);

        if (fd < 0) 
		{
            fprintf(stderr, "Error opening file!");
            exit(4);
        }

        char buff[20];
        ssize_t n;

        while ((n = read(fd, buff, 20)) > 0) 
		{
            buff[n] = '\0';
            printf("%s", buff);
        }

		printf("\n");

        close(fd);
    }
}