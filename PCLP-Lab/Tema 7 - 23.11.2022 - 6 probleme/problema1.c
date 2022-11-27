#include <stdio.h>

//functia swap
void swap(int *pa, int *pb);

int main() {

    int a, b;

    scanf("%d%d", &a, &b);

    swap(&a, &b);

    printf("%d %d", a, b);

    return 0;
    
}

//functia swap
void swap(int *pa, int *pb) {

    int aux;

    aux = (*pa);
    (*pa) = (*pb);
    (*pb) = aux;

}