#include <stdio.h>
#include <stdlib.h>

/* Puzzle A06 -- print the integers from 0 to 14, one per line */
int main(int argc, char *argv[])
{
  int j;
  for (j = 1; j < 100; j += 2)
  {
    printf("%3d\n", j);
  }
  system("PAUSE");
  return 0;
}