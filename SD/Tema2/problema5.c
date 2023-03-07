#include <stdio.h>

int firstBinSearch(int x, int left, int right, int arr[]);
int lastBinSearch(int x, int left, int right, int arr[]);

int main() {
    int v[] = {-1, -1, -1, 0, 0, 2, 52, 52, 52, 52, 52}, x = 52;
    printf("Numarul de aparitii ale lui x este: %d",
        lastBinSearch(x, 0, 10, v) - firstBinSearch(x, 0, 10, v) + 1);
    return 0;
}

int firstBinSearch(int x, int left, int right, int arr[]) {
    int mid = (left + right) / 2;
    while(left < right) {
        if(arr[mid] == x && mid && arr[mid - 1] != x) return mid;
        else if(arr[mid] >= x) right = mid - 1;
             else left = mid + 1;
        mid = (left + right) / 2;
    }
}

int lastBinSearch(int x, int left, int right, int arr[]) {
    int mid = (left + right) / 2, aux = right;
    while(left < right) {
        if(arr[mid] == x && mid < aux && arr[mid + 1] != x) return mid;
        else if(arr[mid] > x) right = mid - 1;
             else left = mid + 1;
        mid = (left + right) / 2;
    }
}