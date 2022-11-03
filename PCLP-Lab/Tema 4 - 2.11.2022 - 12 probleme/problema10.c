#include <stdlib.h>
#include <stdio.h>
#include "myheader.h"

int main() {

    int n, m;

    float* numbers; 
    int* intervals, *counters; 
    //counters tine minte cate numere sunt intr-un interval
    //sunt foarte inspirat cand aleg numele variabilelor

    scanf("%d", &n);

    numbers = (float*) malloc(n * sizeof(float));

    //la fel ca readVector(), doar ca e pt float
    readVectorF(&numbers, n);

    scanf("%d", &m);

    intervals = counters = (int*) malloc(m * sizeof(int));

    readVector(&intervals, m);

    if(!isAscendedOrdered(intervals, m)) printf("Error\n");
    else {

        //sortez numerele reale crescator
        sortVectorF(&numbers, 0, n - 1);

        int i, j;

        i = j = 0;
    
        //Setez toate elementele din counters sa fie 0.
        nullVector(&counters, m);

        //verific intervalele si numerele
        while(i < n && j < m - 1) {

            //daca intervals[j] < numbers[i] < intervals[j + 1] am gasit un numar
            if(numbers[i] <= intervals[j]) i++;
            else if(intervals[j + 1] <= numbers[i]) j++;
                 else {

                    counters[j]++;
                    i++;

                 }


        }

        //afisez cele m - 1 rezultate
        showVector(counters, 0, m - 2);

    }

    return 0;

}

