#include <stdio.h>
#include <stdlib.h>

typedef struct matrice{

        int n, m;
        int** a;

}MATRICE;

MATRICE* creeaza_MATRICE(int n, int m);
MATRICE* citeste_MATRICE(MATRICE* ma);
void scrie_MATRICE(MATRICE* ma);
MATRICE* aduna_MATRICE(MATRICE* ma, MATRICE* mb);
MATRICE* inmulteste_MATRICE(MATRICE* ma, MATRICE* mb);

int main() {

    MATRICE *m, *n, *p;

    m = creeaza_MATRICE(1, 3);
    n = creeaza_MATRICE(3, 2);

    m = citeste_MATRICE(m);
    n = citeste_MATRICE(n);

    p = creeaza_MATRICE(1, 2);

    p = inmulteste_MATRICE(m, n);

    scrie(m); 
    scrie(n);
    scrie(p);

    return 0;
}

MATRICE* creeaza_MATRICE(int n, int m) {

    static MATRICE* ma;

    ma->a = (int**) malloc(n * sizeof(int*));

    for(int i = 0; i < n; i++)
            ma->a[i] = (int*) calloc(m, sizeof(int));

    ma->m = m;
    ma->n = n;

    return ma;
}
MATRICE* citeste_MATRICE(MATRICE* ma) {

    for(int row = 0; row < ma->n; row++)
        for(int col = 0; col < ma->m; col++)
            scanf("%d", &ma->a[row][col]);

    return ma;
}

void scrie_MATRICE(MATRICE* ma) {

    for(int row = 0; row < ma->n; row++) {

        for(int col = 0; col < ma->m; col++)
            printf("%d ", ma->a[row][col]);

        printf("\n");
    }
}

MATRICE* aduna_MATRICE(MATRICE* ma, MATRICE* mb) {

    if(ma->m != mb->m || ma->n != mb->n) return NULL;
    else {

        static MATRICE* mc;
        mc = creeaza_MATRICE(ma->n, ma->m);

        for(int row = 0; row < mb->n; row++)
            for(int col = 0; col < mb->m; col++)
                mc->a[row][col] = ma->a[row][col] + mb->a[row][col];

        return mc;
    }
}

MATRICE* inmulteste_MATRICE(MATRICE* ma, MATRICE* mb) {

    if(ma->m != mb->n) return NULL;
    else {

        static MATRICE* mc;

        mc = creeaza_MATRICE(ma->n, mb->m);

        for(int row = 0; row < ma->n; row++)
            for(int col = 0; col < mb->m; col++)
                for(int k = 0; k < ma->m; k++)
                    mc->a[row][col] += ma->a[row][k] * mb->a[k][col];

        return mc;
    }
}