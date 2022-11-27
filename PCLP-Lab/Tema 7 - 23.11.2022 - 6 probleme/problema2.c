#include <stdio.h>

//tine minte cate numere sunt pozitive, negative si zerouri

void count(int n, int *v, int *zero, int *poz, int *neg);

int main() {

    int vector[101], size, zero, poz, neg;

    zero = poz = neg = 0;

    scanf("%d", &size);

    for(int i = 0; i < size; i++)
        scanf("%d", &vector[i]);

    count(size, vector, &zero, &poz, &neg);

    printf("nule: %d\npozitive: %d\nnegative: %d\n", zero, poz, neg);

    return 0;

}

//tine minte cate numere sunt pozitive, negative si zerouri
void count(int n, int *v, int *zero, int *poz, int *neg) {

    for(int i = 0; i < n; i++)
        if(v[i] > 0) (*poz)++;
        else if(v[i] < 0) (*neg)++;
             else (*zero)++;
    
}