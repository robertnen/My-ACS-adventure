#include <stdio.h>


int main() {

    double x, y;

    scanf("%lf%lf", &x, &y);

    short isOnAxes = (x == 0 || y == 0) ? 1 : 0;

    if(isOnAxes) printf("punct pe axe\n");
    else {
        if(x > 0)  (y > 0) ? printf("1\n") : printf("4\n");
        else (y > 0) ? printf("2\n") : printf("3\n");
    }

    return 0;
}