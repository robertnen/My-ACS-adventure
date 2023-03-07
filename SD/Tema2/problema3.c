#include <stdio.h>

int partition(int left, int right, int arr[]);
int quickSort(int left, int right, int arr[]);

int main() {
    int v[] = {23, 42, 245, 21, -2, -3}, i;
    quickSort(0, 5, v);

    for(i = 0; i < 6; i++) printf("%d ", v[i]);

    return 0;
}

int partition(int left, int right, int arr[]) {
    int pivot = arr[right], index = left - 1, j;
    for(j = left; j < right; j++) {
        if(arr[j] < pivot) {
            arr[++index] ^= arr[j];
            arr[j] ^= arr[index];
            arr[index] ^= arr[j];
        }
    }
    arr[index + 1] ^= arr[right];
    arr[right] ^= arr[index + 1];
    arr[index + 1] ^= arr[right];
    return index + 1;
}

int quickSort(int left, int right, int arr[]) {
    if(left < right) {
        int part = partition(left, right, arr);
        quickSort(left, part - 1, arr);
        quickSort(part + 1, right, arr);
    }
}