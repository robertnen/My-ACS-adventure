#include <stdio.h>

long long int combinariRecursiv(int, int);
long long int factorial(int);
long long int combinari(int, int);

int main() {

    int n, m;
    
    scanf("%d%d", &n, &m);

    printf("Combinari de n luate cate m:\n%llu\n%llu\n", combinariRecursiv(n, m), combinari(n, m));

    return 0;
}

long long int combinariRecursiv(int number, int elementsNumber) {

    return (!elementsNumber) ? 1 : combinariRecursiv(number, elementsNumber - 1) * (number - elementsNumber + 1) / elementsNumber;

}

long long int factorial(int number) {

    long long int result = 1;

    for(int i = 2; i <= number; i++) result *= i;

    return result;
}

long long int combinari(int number, int elementsNumber) {

    return factorial(number) / (factorial(elementsNumber) * factorial(number - elementsNumber));

}