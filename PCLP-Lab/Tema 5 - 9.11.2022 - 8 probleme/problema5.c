#include <stdio.h>

double taylor(double x, int n);
int factorial(int n);
double putere(double x, int n);

int main() {

    double x, result;
    int n;
    
    scanf("%lf%d", &x, &n);

    result = taylor(x, n);

    // result = (int)(result * 10000);
    // result /= 10000;

    printf("%.4lf", result);

    return 0;

}

double taylor(double x, int n) {

    double sum = 0;

    for(int i = 0; i <= n; i++)
        sum += putere(x, i) / factorial(i);

    return sum;

}

int factorial(int n) {

    int product = 1;

    for(int i = 2; i <= n; i++) product *= i;

    return product;

}

double putere(double x, int n) {

    double result = 1;

    for(int i = 1; i <= n; i++) result *= x;

    return result;

}