#include <stdio.h>

int sumOfDigits(int);

int main() {

    int beforeNumber, currentNumber;

    scanf("%d", &beforeNumber);

    while(beforeNumber != 0) {

        scanf("%d", &currentNumber);

        if(beforeNumber % sumOfDigits(beforeNumber) == currentNumber)
            printf("(%d, %d)\n", beforeNumber, currentNumber);

        beforeNumber = currentNumber;
    }

    return 0;
}

inline int sumOfDigits(int number) {

    int sum = 0;
    while(number) sum += number % 10, number /= 10;
    return sum;
}