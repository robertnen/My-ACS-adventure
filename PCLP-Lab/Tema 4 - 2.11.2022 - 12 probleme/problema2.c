#include <stdlib.h>
#include <stdio.h>

int main() {

    int n, numOfPos, numOfNeg;
    
    numOfNeg = numOfPos = 0;

    scanf("%d", &n);

    int* numbers = (int*) malloc(n * sizeof(int));

        for(int i = 0; i < n; i++) {

        scanf("%d", numbers + i);

        //nu mai fac cu ? : si folosesc if: 
        if(numbers[i] < 0) numOfNeg++;
        else numOfPos++;

    }

    free(numbers);

    printf("%d %d", numOfNeg, numOfPos);

    return 0;
}