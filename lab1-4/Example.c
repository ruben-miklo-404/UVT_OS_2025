#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    int found_o = 0;
    char *myArg;

    printf("This is the number of arguments: %d\n", argc);

    for (int i = 0; i < argc; i++)
    {
        printf("This is argument %i: %s\n", i, argv[i]);

        if(strcmp(argv[i], "-o") == 0)
        {
            printf("Found option -o\n");

            found_o = 1;

            if(argv[i + 1])
            {
                myArg = argv[i + 1];

                printf("This is the option -o argument");
                printf("%s\n", myArg);

                i++;
            }
            else
            {
                printf("No argument option for option -o\n");
            }
        }

        if (!found_o)
        {
            printf("-o not found\n");
        }
    }
}