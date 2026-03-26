// 2. Create a C application able to create folders. The folder name will be given as a command-line argument (first argument, after the executable path)
// at execution.
// -The application will compile the source code for the above exercise.
// -The application will run the executable from the previous exercise, with the same arguments as the ones received at execution.

// E.g: ./a.out myfolder Today is sunny
// Will result in the folder myfolder being created, containing the myfolder file. Furthermore, both the STDOUT and the myfolder/myfolder file 
// are containing/printing Todayissunny

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>

int main(int argc, char** argv)
{
    char* filepath = malloc(sizeof(2 * strlen(argv[1]) + 2));
    strcpy(filepath, argv[1]);
    strcat(filepath, "/");
    strcat(filepath, argv[1]);
    
    if (argc <= 2) 
	{
        fprintf(stderr, "Requires 2 arguments, file name and message! %s\n", strerror(errno));
        exit(1);
    }

    pid_t subprocess_id = fork();
    
    if (subprocess_id < 0) 
	{
        fprintf (stderr, "Error creating child! %s\n", strerror(errno));
        exit(2);
    }

    if(subprocess_id == 0)
    {
        if(mkdir(argv[1], 0777) == -1)
        {
            printf("Error creating the directory! %s\n", strerror(errno));
            exit(3);    
        }

        int fd = open(filepath, O_CREAT | O_WRONLY | O_TRUNC, 0660);
        if (fd < 0) 
		{
            fprintf(stderr, "Error opening file %s in subprocess! %s\n", filepath, strerror(errno));
            exit(4);
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
        int subprocess_status;

        waitpid(subprocess_id, &subprocess_status, 0);

        int fd = open(filepath, O_RDONLY);
        if (fd < 0) 
		{
            fprintf(stderr, "Error opening file %s in main process! %s\n", filepath, strerror(errno));
            exit(5);
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