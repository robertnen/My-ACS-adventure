#include <stdio.h>

//sorteaza un vector crescator folosind metoda Bubble Sort
void bubbleSort(int vector[], int size);

int main() {

    int n, vector[101];

    //citirea
    scanf("%d", &n);

    //citirea
    for(int i = 0; i < n; i++)
        scanf("%d", &vector[i]);

    //sortarea
    bubbleSort(vector, n);

    //afisarea
    for(int i = 0; i < n; i++)
        printf("%d ", vector[i]);

    return 0;
}

//sortarea vectorului prin metoda BubbleSort
void bubbleSort(int vector[], int size) {

    int aux;
    short isSorted = 0;

    while(!isSorted) {

        //presupun ca e sortat
        isSorted = 1;

        for(int i = 0; i < size - 1; i++)
            if(vector[i] > vector[i + 1]) {

                //fac swap
                aux = vector[i];
                vector[i] = vector[i + 1];
                vector[i + 1] = aux;

                //vectorul nu este sortat
                isSorted = 0;
            }
    }

}