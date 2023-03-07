#include <stdio.h>
#include <stdlib.h>

/* Puzzle A01 -- print the integers from 0 to 14, one per line */
int main(int argc, char *argv[])
{
  int j;
  for (j = 0; j < 25; j++)
  {
    printf("%3d ", j);
    if(j % 5 == 4) printf("\n");
  }
  system("PAUSE");
  return 0;
}