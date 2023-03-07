#include <stdio.h>
#include <math.h>

double absDiff(double a, double b) {return (a > b ? a - b : b - a);}
double nthRoot(int, int);

const double EPSILON = 0.001;

int main() {
    printf("sqrt(2) = %.3lf\n", nthRoot(2, 2));
    int i;
    return 0;
}

double nthRoot(int num, int n) {
    double low, high, mid, aux;
    if(num == 1) return 1;
    low = (num < 1 ? 0 : 1);
    high = (num < 1 ? 1 : num);
    mid = (high + low) / 2;
    aux = pow(mid, n);
    while(absDiff(aux, num) >= EPSILON) {
        if(aux > num) high = mid;
        else low = mid;
        mid = (high + low) / 2;
        aux = pow(mid, n);
    }
    return mid;
}