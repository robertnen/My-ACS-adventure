#include <stdio.h>

int cmmmc(int a, int b);

int main() {

    int x1, x2, y1, y2;

    scanf("%d%d%d%d", &x1, &y1, &x2, &y2);

    int y = cmmmc(y1, y2);

    x1 = x1 * y / y1;
    x2 = x2 * y / y2;

    printf("%d %d\n%d %d\n", x1, y, x2, y);

    return 0;

}

int cmmmc(int a, int b) {

    int product = a * b;

    while(a != b) {

        if(a > b) a -= b;
        else b -= a;

    }

    return product / a;

}
