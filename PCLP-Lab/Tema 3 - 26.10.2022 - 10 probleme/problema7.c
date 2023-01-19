#include <stdio.h>
#include <math.h>

double expSum(double, int);
double expSumRecursive(double, int);

int main() {

    int n, step;
    double x, eps, sum = 0;

    scanf("%lf%d%lf", &x, &n, &eps);

    step = 0;

    //inca incerc sa inteleg enuntul de o ora... Asa trebuia? Mi-a dat ca in exemplu
    //dar sunt pierdut in spatiu :))
    while(eps < expSumRecursive(x, step)) sum += expSumRecursive(x, step++);

    printf("%lf %lf %lf %lf", expSum(x, n), sum, exp(x), pow(2.718, x));

    return 0;
}

double expSum(double x, int n) {

    double result = 1, powerOfX = 1;
    long long int product = 1;

    for(int i = 1; i < n; i++) {

        product  *= i;
        powerOfX *= x;

        result += powerOfX / product;

    }

    return result;
}

double expSumRecursive(double x, int step) {

    return (!step) ? 1 : expSumRecursive(x, step - 1) * x / step;

}