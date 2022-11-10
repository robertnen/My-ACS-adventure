#include <stdio.h>

int transforma(int n);

int main() {

    int n;

    //citire
    scanf("%d", &n);

    n = transforma(n);

    //afisare
    printf("%d", n);

    return 0;

}

int transforma(int n) {

    //daca n e 0 atunci raspunsupul este 0
    if(!n) return 0;

    int aux = n, ap[10] = {0};
    short withoutZero = 1;

    //verific daca numarul are 0
    while(aux) {

        if(aux % 10 == 0) {

            withoutZero = 0;
            break;
        }

        aux /= 10;
    }

    //tin minte cate aparitii are fiecare cifra din n
    while(n) {

        ap[n % 10]++;
        n /= 10;

    }

    //daca nu am 0 ordonez crescator
    if(withoutZero) {

            for(int i = 1; i < 10; i++)
                while(ap[i]) {

                    n = n * 10 + i;
                    ap[i]--;

                }
      //am cel putin un 0, deci ordonez descrescator
    } else {

        for(int i = 9; i > -1; i--)
                while(ap[i]) {

                    n = n * 10 + i;
                    ap[i]--;

                }
    }

    return n;
}