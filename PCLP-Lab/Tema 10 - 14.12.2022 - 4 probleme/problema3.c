#include <stdio.h>
#define MAX 20

typedef struct MATERIA {

    char nume[15];
    int ore_curs;
    enum {C = -1, S = 0, A = 1} tip_examen;

} materie;

int main() {

    materie PROGRAMA[MAX];

    return 0;
}