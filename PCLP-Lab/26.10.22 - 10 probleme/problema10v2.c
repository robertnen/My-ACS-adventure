/*
    Nu am gasit foaie ca sa gandesc pe ea formula asa ca o scriu aici

    1    -> 9            => 9 * 10^0 numere => 9 * 10^0 * 1 cifre
    10   -> 99           => 9 * 10^1 numere => 9 * 10^1 * 2 cifre
    100  -> 999          => 9 * 10^2 numere => 9 * 10^2 * 3 cifre
    .................................................................................................
    10^k -> 10^(k+1) - 1 => 9 * 10^k numere => 9 * 10^k * (k + 1) cifre

    10^(k+1) -> n < 10^(k+2) - 1 => n + 1 - 10^(k + 1) numere => (n + 1 - 10^(k + 1)) * (k + 2) cifre

    numarul de cifre = 9 * Σ (10^k * (k + 1)) + (n + 1 - 10^[log n]) * ([log n] + 1)

    [log n] = k + 1 in ce am facut mai sus


    Notez [log n] = n pentru a fi mai usor de citit

    Σ (10^k * (k + 1)) = Σ Σ 10^(i - 1) = Σ 10^(k - 1) * Σ 10^(i - 1) =

    = Σ 10^(k - 1) * (10^(n - k + 1) - 1) / 9 = 1 / 9 * Σ (10^n - 10^(k - 1)) =

    = n * 10 ^ n / 9 - 1 / 9 * Σ 10^(k - 1) = n * 10^n / 9 - (10^n - 1) / 81 =

    = (9 * n * 10^n - 10^n + 1) / 81

    => numarul de cifre = (9 * [log n] * 10^[log n] - 10^[log n] + 1) / 9 + (n + 1 - 10^[log n]) * ([log n] + 1)

*/

#include <stdio.h>

int getLogOf10(long long int);

int main() {

    long long int n, powerOfTen = 1, numberOfDigits = 0;

    scanf("%llu", &n);

    int log = getLogOf10(n), clog = log;

    //calculez 10^[log n]
    while(clog) {
        if(clog % 2) {
            
            powerOfTen *= 10;
            clog--;
        } else powerOfTen *= 100, clog -= 2;
    }

    numberOfDigits  = (powerOfTen * ( 9 * log - 1) + 1) / 9;
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