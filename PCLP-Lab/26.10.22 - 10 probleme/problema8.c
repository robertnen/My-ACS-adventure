#include <stdio.h>

//am stat 10 minute ca sa realizez ca abs() returneaza doar in int...
double abs(double x) {return (x < 0) ? -x : x;}

int main() {

    double x, r1, r2, eps;

    scanf("%lf%lf", &x, &eps);

    r1 = x / 2;
    r2 = x / 4 + 1;

    while(abs(r1 - r2) >= eps)  r1 = r2, r2 = (r1 + x / r1) / 2; 

    printf("%lf %lf", r2, sqrt(x));

    return 0;
}