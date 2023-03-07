#include <stdio.h>
#include <stdlib.h>

/* Puzzle A07 -- print the first N odd integers. Ask the user for N. */
int main(int argc, char *argv[])
{
  int j, N;

  printf("Enter N: ");
  scanf("%d", &N );

  for (j = 1; j < 2 * N + 1; j += 2)
  {
    printf("%3d\n", j);
  }
  system("PAUSE");
  return 0;
}