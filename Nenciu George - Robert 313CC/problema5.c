#include <stdio.h>

int main() { 

    int a, b, c;

    scanf("%d%d%d", &a, &b, &c);

    short isNegative = (a < 0 || b < 0 || c < 0) ? 1 : 0;

    if(isNegative) printf("NU\n");
    else {

        (a  <= b + c) ? printf("DA") : printf("NU");

    }

    return 0;
}