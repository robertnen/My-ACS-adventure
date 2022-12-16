#include <stdio.h>
#include <stdlib.h>

typedef struct ComplexNumbers {

    float real, imaginary;
} complex;

complex adunare(complex a, complex b);
complex scadere(complex a, complex b);
complex inmultire(complex a, complex b);
complex putere(complex a, int putere);
void scrie(complex a);

int main() {

    complex variable, b = {0, 0}, polynom = {0, 0};

    int size;
    float coefficients[5];

    printf("Partea reala: ");

    scanf("%f", &variable.real);

    printf("Partea imaginara: ");

    scanf("%f", &variable.imaginary);

    printf("Numarul de coeficienti ( < 6 ): ");

    scanf("%d", &size);

    for(int i = 0; i < size; i++) {

        printf("Coeficient: ");
        scanf("%f", &coefficients[i]);
    
        b.real = coefficients[i];
        b.imaginary = 0;

        b = inmultire(b, putere(variable, i));

        polynom = adunare(polynom, b);
    }

    printf("Polinomul are valoarea: ");
    scrie(polynom);

    return 0;
}

complex adunare(complex a, complex b) {

    complex result = {0, 0};

    result.real = a.real + b.real;
    result.imaginary = a.imaginary + b.imaginary;

    return result;
}

complex scadere(complex a, complex b) {

    complex result = {0 , 0};

    result.real = a.real - b.real;
    result.imaginary = a.imaginary - b.imaginary;

    return result;
}

complex inmultire(complex a, complex b) {
    
    complex result = {1, 1};

    result.real = a.real * b.real - a.imaginary * b.imaginary;
    result.imaginary = a.real * b.real + a.imaginary * b.imaginary;

    return result;
}

complex putere(complex a, int putere) {

    complex result = {1, 1};

    for(int i = 0; i < putere; i++) {

        result.real = a.real * result.real - a.imaginary * result.imaginary;
        result.imaginary = a.real * result.real + a.imaginary * result.imaginary;
    }
    
    return result;
}

void scrie(complex a) {

    printf("(%f, %f)\n", a.real, a.imaginary);
}