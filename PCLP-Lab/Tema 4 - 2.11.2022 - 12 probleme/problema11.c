#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "myheader.h"

//calculez suma normal
double polySum(double x, int n, int* coefficients);

//pSR = polySumRecursive
double pSR(double x, int* coefficients, int step, int n);

int main() {

    int n;
    double x;
    
    scanf("%lf%d", &x, &n);

    int* coefficients = (int*) malloc((n + 1) * sizeof(int));

    readVector(&coefficients, n + 1);

    double result1, result2;

    result1 = polySum(x, n, coefficients);
    result2 = pSR(x, coefficients, n, n);

    //ca sa nu imi aproximeze gresit
    result1 = floor(result1 * 100) / 100;
    result2 = floor(result2 * 100) / 100;

    printf("%.2lf %.2lf", result1, result2);

    return 0;

}

double polySum(double x, int n, int* coefficients) {

    //daca x = 0, atunci polinomul e o constanta
    if(!x) return coefficients[n];

    double sum = 0, powX;

    powX = pow(x, n);

    for(int i = n; i > -1; i--) {

        sum += powX * coefficients[n - i];
        powX /= x;
    }

    return sum;
}

double pSR(double x, int* coefficients, int step, int n) {

    if(!step) return coefficients[0]; //termenul liber
    return pSR(x, coefficients, step - 1, n) * x + coefficients[step];

}