#include <stdio.h>

int transforma(int n);

int main() {

    int n;

    scanf("%d", &n);

    n = transforma(n);

    printf("%d", n);

    return 0;

}

int transforma(int n) {

    if(!n) return 0;

    int aux = n, ap[10] = {0};
    short withoutZero = 1;

    while(aux) {

        if(aux % 10 == 0) {

            withoutZero = 0;
            break;
        }

        aux /= 10;
    }

    while(n) {

        ap[n % 10]++;
        n /= 10;

    }

    if(withoutZero) {

            for(int i = 1; i < 10; i++)
                while(ap[i]) {

                    n = n * 10 + i;
                    ap[i]--;

                }

            return n;
            
    } else {

        for(int i = 9; i > -1; i--)
                while(ap[i]) {

                    n = n * 10 + i;
                    ap[i]--;

                }

            return n;
    }
}