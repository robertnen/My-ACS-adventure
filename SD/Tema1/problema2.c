#include <stdio.h>

long int productArr(int arr[], int size);

int main() {
    int v[] = {1, 1, 2, 3, 4, 5, 6, 1, 1};
    printf("%d", productArr(v, 9));
    return 0;
}

long int productArr(int arr[], int size) {
    return (!size ? 1 : arr[size - 1] * productArr(arr, size - 1));
}