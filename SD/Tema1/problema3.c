#include <stdio.h>

int fiboGen(int n, int k);

int main() {
    printf("%d", fiboGen(5, 3));
    return 0;
}

int fiboGen(int n, int k) {
    if(n < k) return 1;
    int index;
    long int sum = 0;
    for(index = 1; index <= k; index++) {
        sum += fiboGen(n - index, k);
    }
    return sum;
}