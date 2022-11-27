#include <stdio.h>

void transform(int v[], int n, int x);

int main() {

    int size, value, vector[101];

    //citirea
    scanf("%d%d", &size, &value);

    for(int i = 0; i < size; i++)
        scanf("%d", &vector[i]);

    //modific vectorulul dupa cum s-a cerut
    transform(vector, size, value);

    //afisarea
    for(int i = 0; i < size; i++)
        printf("%d ", vector[i]);

    return 0;
}

//criteriul nu e specificat in enunt dar aparent e nevoie de el...
void transform(int v[], int n, int x) {

    //asta tine minte unde se afla ultima valoare mai mica decat x cunoscuta
    int pos = 0, aux;

    for(int i = n - 1; i > pos; i--) {

        if(v[i] < x) {

            //caut primul element care trebuie schimbat (daca exista)
            while(v[pos] < x) pos++;

            //verific daca cumva fac swap cu un numar bun
            if(pos > i) continue;

            //swap
            aux = v[i];
            v[i] = v[pos];
            v[pos] = aux;

        }
    }

}