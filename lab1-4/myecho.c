#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
  int i;

  for (i=1; i<argc; i++)
    printf("Argument %d is: %s\n", i, argv[i]);

  exit(0);
}

// #include <math.h>
// #include <stdio.h>
//
// int main(void)
// {
//   printf("The value of pi is: ");
//   printf("%f", 2 * asin(1));
//   printf("\n");
//   return 0;
// };