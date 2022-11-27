#include <stdio.h>
#include <limits.h>

//calculeaza panta
void panta(int x1, int y1, int x2, int y2, float *m, float *n);

int main() {

    //declararea
    int p_1, p_2, p_3, p_4, p_5, p_6;

    //citirea
    scanf("%d%d%d%d%d%d", &p_1, &p_2, &p_3, &p_4, &p_5, &p_6);

    float m, n;

    //calculez panta si ordonata
    panta(p_1, p_2, p_3, p_4, &m, &n);
    
    //afisarea
    if(p_6 == m * p_5 + n) printf("Da\n");
    else printf("Nu\n");

    return 0;

}

//calculeaza panta
void panta(int x1, int y1, int x2, int y2, float *m, float *n) {

    //dreapta e verticala
    if(y2 == y1) {

        (*m) = INT_MAX;
        (*n) = y1;    
    
    } else { //nu e verticala

        (*m) = (x2 * .1 - x1) / (y2 * .1 - y1);
        (*n) = y1 - (*m) * x1;

    }
}
