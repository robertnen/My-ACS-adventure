#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main() {

    long int seed = time(0);

    srand(seed);

    printf("%d %d %d", rand(), rand(), rand());

    return 0;
}