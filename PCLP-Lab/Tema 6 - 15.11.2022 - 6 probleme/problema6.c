#include <stdio.h>

//pun rezultatul intr-un vector V
void spirala (int A[][100], int m, int n, int V[]);

//afisare
void afisare(int V[], int dim);

int main() {

    int matrix[101][101], vector[101];
    int row, col;

    //citire
    scanf("%d%d", &row, &col);

    for(int i = 0; i < row; i++)
        for(int j = 0; j < col; j++)
            scanf("%d", &matrix[i][j]);

    spirala(matrix, row, col, vector);

    //afisare
    afisare(vector, row * col);

    return 0;
}

//pun rezultatul intr-un vector V
void spirala (int A[][100], int m, int n, int V[]) {

    for(int i = 0; i < m; i++)
        for(int j = i + 1; j < n; j++)
            printf("%d %d") ; // de terminat !!!!!!!!!!!!!!!!!!!!!!!!!!!
}

//afisare
void afisare(int V[], int dim) {

    for(int i = 0 ; i < dim; i++)
        printf("%d ", V[i]);
}