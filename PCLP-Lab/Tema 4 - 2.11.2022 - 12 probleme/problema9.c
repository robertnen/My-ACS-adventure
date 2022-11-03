#include <stdlib.h>
#include <stdio.h>
#include "myheader.h"

int main() {

    int *vector, size;

    scanf("%d", &size);

    readVector(&vector, size);

    //verific natura sirului
    if(isConstant(vector, size)) printf("constant\n");
    else if(isAscendedOrdered(vector, size)) printf("crescator\n");
         else if(isDescendedOrdered(vector, size)) printf("descrescator\n");
              else printf("neordonat\n");

    free(vector);

    return 0;

}
