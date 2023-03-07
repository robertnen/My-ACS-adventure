#include <stdio.h>
#include <stdlib.h>

void merge(int arr[], int left, int mid, int right) {
    int size1 = mid - left + 1; //size of the first array
    int size2 = right - mid;    // -,- of the 2nd array

    int* leftArr, *rightArr; //temporary arrays
    leftArr = (int*) malloc(size1 * sizeof(int));
    rightArr = (int*) malloc(size2 * sizeof(int));

    int i, j, k;
    for(i = 0; i < size1; i++) //copy 1st array
        leftArr[i] = arr[left + i];

    for(j = 0; j < size2; j++) //copy 2nd array
        rightArr[j] = arr[mid + j + 1];

    i = j = 0; k = left;

    //sorted merge
    while(i < size1 && j < size2)
        arr[k++] = (leftArr[i] < rightArr[j] ? leftArr[i++] : rightArr[j++]);

    while(i < size1) arr[k++] = leftArr[i++];
    while(j < size2) arr[k++] = rightArr[j++];

    //truly useless
    free(leftArr);
    free(rightArr);
}

void mergeSort(int arr[], int left, int right) {
    if(left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

int main() {
    int toSortArray[] = {2, 4, 32, 542, 536, 23, 1, 1, 24, 5};
    mergeSort(toSortArray, 0, 10 - 1);
    for(int i = 0; i < 10; i++)
        printf("%d ", toSortArray[i]);
}