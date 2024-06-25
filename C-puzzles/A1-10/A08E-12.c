#include <stdio.h>
#include <stdlib.h>

/* Puzzle A08 -- print the first N odd integers. Ask the user for N. */
int main(int argc, char *argv[])
{
  int j, N, so = 0, se = 0;

  printf("Enter N: ");
  scanf("%d", &N );

  for(j = 0; j <= N; j++)
    if(j % 2) so += j;
    else se += j;

  printf("Sum = %d, Sum of Odd = %d, Sum of Even = %d\n", se + so, so, se);
  system("PAUSE");
  return 0;
}
