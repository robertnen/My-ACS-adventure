#include <stdio.h>

double taylor(double x, int n);
int factorial(int n);
double putere(double x, int n);

int main() {

    double x, result;
    int n;
    
    //citire
    scanf("%lf%d", &x, &n);

    result = taylor(x, n);

    // las asta aici chiar daca nu e ok
    // la unele cazuri nu imi da rezultatul fara urmatoarele 2 randuri
    // result = (int)(result * 10000);
    // result /= 10000;

    printf("%.4lf", result);

    return 0;

}

//suma taylor
double taylor(double x, int n) {

    double sum = 0;

    // sum = Σ x^n / n!
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