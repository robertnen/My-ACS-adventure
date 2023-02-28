#include <stdio.h>

int counterArr(int arr[], int size, int value);

int main() {
    int v[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    printf("%d", counterArr(v, 9, 7));
    return 0;
}

int counterArr(int arr[], int size, int value) {
    if (!size) return 0;
    return (arr[size - 1] < value ? 0 : 1) + counterArr(arr, size - 1, value);
}