//rezolvarea unei ecuatii de gradul al II-lea

#include <stdio.h>
#include <math.h>

int main() {

    double a, b, c;

    scanf("%lf%lf%lf", &a, &b, &c);

    //verific mai intai cazurile in care a == 0
    if(a == 0 && b == 0 && c == 0) printf("Exista o infinitate de solutii!\n");
    else if(a == 0 && b == 0) printf("Nu exista solutii!\n");
         else if(a == 0) printf("%0.2lf", (-c / b));
              else {

                double delta = b * b - 4 * a * c;
               
               /*
                    Daca delta < 0, radacinile sunt in C \ R, deci nu sunt numere
                    reale, altfel acestea exista.
               */

                if(delta < 0) printf("Nu are solutii!\n");
                else if(delta == 0) printf("%0.2lf", -b/ (2 * a));
                     else printf("%0.2lf %0.2lf", (-b - sqrt(delta)) / (2 * a), (-b + sqrt(delta)) / (2 * a));

              }


    return 0;
}