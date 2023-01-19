#include <stdio.h>

typedef enum {false = 0, true = 1} bool; //bool_t

bool isPrime(int);

int main() {

    int n;

    unsigned long long int a, b, c;

    a = b = 1;

    scanf("%d", &n);

    //deja am 3 numere... de cand 0 e in sirul lui Fibo?
    for(int i = 2; i < n - 1; i++) {

        c = a + b;
        a = b;
        b = c;

        if(isPrime(c)) printf("%llu\n", c);

    }

    return 0;
}

bool isPrime(int number){

    if(number < 2 || !(number % 2)) return false;
    if(number == 2) return true;
    
    for(int i = 3; i * i <= number; i += 2)
        if(!(number % i)) return false;

    return true;

}