#include <stdio.h>

//citeste un vector si dimensiunea acestuia
void read(int vector[], int* size);

//sorteaza un vector crescator folosind metoda Bubble Sort
void bubbleSort(int vector[], int size);


int main() {

    int a[101], b[101], c[101];
    int sizeA, sizeB, sizeC;

    sizeC = 0;

    //citirea vectorilor si a dimensiunilor
    read(a, &sizeA);
    read(b, &sizeB);

    //parcurgerea vectorilor
    for(int i = 0; i < sizeA; i++)
        for(int j = 0; j < sizeB; j++)
            if(a[i] == b[j]) c[sizeC++] = b[j];
    
    //afisarea
    for(int i = 0; i < sizeC; i++)
        printf("%d ", c[i]);

}

//citeste un vector si dimensiunea acestuia
void read(int vector[], int* size) {

    scanf("%d", size);

    for(int i = 0; i < (*size); i++) 
        scanf("%d", &vector[i]);

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