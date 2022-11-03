#include <stdlib.h>
#include <stdio.h>
#include "myheader.h"

int main() {

    int *vector, size;

    //iPos = pozitia initiala 
    //fPos = pozitia finala
    //iPos_max si fPos_max retin unde se afla cel mai lung sir ordonat crescator
    int iPos, fPos, iPos_max, fPos_max, maxLength, currentLength, beforeNumber;

    iPos = fPos = iPos_max = fPos_max = maxLength = currentLength = 0;

    scanf("%d", &size);

    readVector(&vector, size);

    beforeNumber = vector[0];

    for(int i = 0; i < size; i++) {

        if(beforeNumber > vector[i]) {
            
            if(currentLength > maxLength) {

                maxLength = currentLength;
                iPos_max = iPos;
                fPos_max = fPos - 1;

            }

            currentLength = 0;
            iPos = fPos;

        } else currentLength++; 

        fPos++;
        beforeNumber = vector[i];
        
    }
        

    //afisez secventa cea mai lunga...
    showVector(vector, iPos_max, fPos_max);

    free(vector);

    return 0;
}