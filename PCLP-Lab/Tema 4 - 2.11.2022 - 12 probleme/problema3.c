#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

int main() {

    int row, col;

    scanf("%d%d", &row, &col);

   int **array = (int**) malloc(row * sizeof(int*));

   for(int i = 0; i < row; i++) {

        array[i] = (int*) malloc(col * sizeof(int));

        for(int j = 0; j < col; j++)
            scanf("%d", &array[i][j]);

   }

   int maximum, saddle;
   bool isFirstTime = true;

   for(int i = 0; i < row; i++) {

        maximum = array[i][0];

        for(int j = 1; j < col; j++)
            if(maximum < array[i][j]) maximum = array[i][j];

        if(isFirstTime) saddle = maximum, isFirstTime = false;
        else if(saddle > maximum) saddle = maximum;

   }

    free(array);

    printf("%d", saddle);

    return 0;
}