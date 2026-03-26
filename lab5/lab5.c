#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	int id[10], status[10];
	for(int i = 0; i < 10; i++)
	{
		id[10] = fork();
		if(id[i] > 0)
		{
			wait(&status[i]);
			// printf("this is the parent process with fork return value of %d\n", id);
			// printf("the PID of the process (parent) returned by getpid is %d\n", getpid());
			// printf("the PID of the parent process of the parent returned by getppid is %d\n", getppid());
			printf("the exit code of the child is %d\n", WEXITSTATUS(status[i]));
		}
			else if(id[i] == 0)
			{
				if(i == 0)
				{
					execlp("gcc", "gcc", "file.c", "-o", "/home/ruben/ruben_OS/file", NULL);
					fprintf(stderr, "Error running gcc \n");
				}
				else
				{
					execlp(".//home/ruben/ruben_OS/file", ".//home/ruben/ruben_OS/file", NULL);
					fprintf(stderr, "Error running the app\n");
				}

				// printf("this is the child process with fork return value of %d\n", id);
				// printf("the PID of the process (child) returned by getpid is %d\n", getpid());
				// printf("the PID of the parent process of the child returned by getppid is %d\n", getppid());
				exit(i);
			}
			else
			{
				
				fprintf(stderr, "Error creating a new process %d\n", id[i]);
				exit(1);
			}
	}

	// for(int i = 0; i < 10; i++)
	// {
	// 	//wait(&status); // first process to finish execution
	// 	waitpid(id[i], &status[i], 0);
	// 	printf("The exit code of the child is %d\n", WEXITSTATUS(status[i]));
	// }
	return 24;
}