#include <stdlib.h>
#include <stdio.h>
#include "myheader.h"

int main() {

    int *vector, size, sum, maxSum;

    scanf("%d", &size);

    readVector(&vector, size);

    //iPos = pozitia initiala 
    //fPos = pozitia finala
    //iPos_max si fPos_max retin unde se afla cel mai lung sir ordonat crescator
    int iPos, fPos, iPos_max, fPos_max;

    iPos = fPos = iPos_max = fPos_max = sum = maxSum = 0;


    for(int i = 0; i < size; i++) {

        //iau alta secventa
        if(sum < 0) {

            sum  = 0; 
            iPos = i;
        }

        sum += vector[i];

        if(sum > maxSum) {

            maxSum   = sum;
            iPos_max = iPos;
            fPos_max = fPos;

        }

        fPos++;
        
    }

    showVector(vector, iPos_max, fPos_max);

    free(vector);

    return 0;

}