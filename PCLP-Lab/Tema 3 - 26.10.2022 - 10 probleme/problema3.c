#include <stdio.h>

int main() {

    int n;
    float x, sumOfX;
    double y, sumOfY;

    sumOfX = sumOfY = 0;

    scanf("%d%f%lf", &n, &x, &y);

    for(int i = 1; i <= n; i++) {

        sumOfX += x; sumOfY += y;

        if(i % (n / 10) == 0) printf("%f\t%e\t%f\t%e\n", sumOfX, sumOfX, sumOfY, sumOfY);
    }

    return 0;
}