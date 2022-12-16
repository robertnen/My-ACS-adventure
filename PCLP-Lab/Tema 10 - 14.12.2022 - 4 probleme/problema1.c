#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double integrala(double (*func) (double x), double a, double b, int n);

int main() {

    double a, b;
    int n;

    printf("a, b, n: ");
    scanf("%lf%lf%d", &a, &b, &n);

    printf("Rezultate pt sin si cos: %lf %lf\n", integrala(sin, a, b, n), integrala(cos, a, b, n));

    return 0;
}

double integrala(double (*func) (double x), double a, double b, int n) {

    double h = (b - a) / n, x_1, x_2, sum;

    x_1 = a;
    sum = 0;

    //Δk = a + (b - a) * k / n;
    for(int i = 2; i <= n; i++) {

        x_2 = a + (b - a) * i / n;
    
        sum += func(x_1) + func(x_2);

        x_1 = x_2;
    }

    return sum * h / 2;

}