/*
    Nu am gasit foaie ca sa gandesc pe ea formula asa ca o scriu aici

    1    -> 9            => 9 * 10^0 numere => 9 * 10^0 * 1 cifre
    10   -> 99           => 9 * 10^1 numere => 9 * 10^1 * 2 cifre
    100  -> 999          => 9 * 10^2 numere => 9 * 10^2 * 3 cifre
    .................................................................................................
    10^k -> 10^(k+1) - 1 => 9 * 10^k numere => 9 * 10^k * (k + 1) cifre

    10^(k+1) -> n < 10^(k+2) - 1 => n + 1 - 10^(k + 1) numere => (n + 1 - 10^(k + 1)) * (k + 2) cifre

    numarul de cifre = 9 * Σ (10^k * (k + 1)) + (n + 1 - 10^([log n] + 1)) * ([log n] + 1)

    [log n] = k + 1 in ce am facut mai sus

*/
#include <stdio.h>

int getLogOf10(long long int);

int main() {

    long long int n, powerOfTen = 1, numberOfDigits = 0;

    scanf("%llu", &n);

    int log = getLogOf10(n);

    //calculez ce e in Σ
    for(int i = 0; i < log; i++) {

        numberOfDigits += powerOfTen * (i + 1);
        powerOfTen *= 10; 

    }

    numberOfDigits *= 9;
    numberOfDigits += (n + 1 - powerOfTen) * (log + 1);

    printf("%llu", numberOfDigits);

    return 0;
}

int getLogOf10(long long int n) {

    int log, p;

    log = 0; p = 1;

    while(n >= p) p *= 10, log++;

    // vreau prima putere a lui 10 mai mica decat n
    return --log;
}