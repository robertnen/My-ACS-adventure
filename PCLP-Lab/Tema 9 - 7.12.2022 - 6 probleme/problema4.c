#include <stdio.h>
#include <stdlib.h>

typedef struct Vector{

    int* v;
    int cap;
    int n;

} vector;

void init_vector(vector* a, int nr);
void adauga_vector(vector* a, int n);
void scrie_vector(vector a);

int main() {

    vector vect;

    init_vector(&vect, 101);

    for(int i = 0; i < 101; i++)
        adauga_vector(&vect, i);

    scrie_vector(vect);

    free(vect.v);

    return 0;
}

void init_vector(vector* a, int nr) {
    
    a->n = 0;
    a->cap = nr;
    a->v = (int*) malloc(nr * sizeof(int));
}

void adauga_vector(vector* a, int n) {

    if(a->cap < a->n)
        a->v = realloc(a->v, 2 * a->n * sizeof(int));
    
    a->v[a->n++] = n;
}

void scrie_vector(vector a) {

    for(int i = 0; i < a.n; i++)
        printf("v[%d] = %d\n", i, a.v[i]);
}