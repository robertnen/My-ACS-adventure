#include <stdio.h>

int f(int, int[]);

int main() {
    int v[] = {-1, -1, -1, -1, -1, -1, -1, -1, -1};
    printf("f(4) = %d\n", f(4, v));
    return 0;
}

int f(int k, int arr[]) {
    if(k < 3) return 1;
    if(arr[k] > 0) return arr[k];
    arr[k] = f(k - 1, arr) + f(k - 2, arr) + f(k - 3, arr);
    return arr[k];
}