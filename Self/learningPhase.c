#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/unistd.h>

#define BUF_SIZE 1024

//Reading files, printing data from file

int main(int argc, char *argv[])
{
    int fd = open(argv[1], O_RDONLY);
    char buf[BUF_SIZE];

    if(fd != -1)
    {
        ssize_t numRead = read(fd, buf, BUF_SIZE - 1);
        
        while(numRead > 0)
        {
            buf[numRead] = '\0';
            printf("%s\n", buf);
            numRead = read(fd, buf, BUF_SIZE - 1);
        }


        return 0;
    }
    else
    {
        printf("Error opening file!\n");
        return -1;
    }
}


// Pipes in UNIX    

// void main()
// {
//     int pipefds[2];
//     char buffer[256] = {0};

//     printf("parent pid: %d\n", getpid());
//     pipe(pipefds);
//     write(pipefds[1], "msg", 3);

//     if (fork() > 0)
//     {
//         return;
//     }
    
//     read(pipefds[0], buffer, 3);
    
//     printf("got from pipe: %s\n", buffer);
//     printf("child pid: %d\n", getpid());
// }