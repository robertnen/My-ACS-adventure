//afisarea unui tabel cu x, sin x si cos x a valorilor de la 0 la 2 * PI cu contor PI / 20

#include <stdio.h> 
#include <math.h> 
 
int main()  { 

     double x, PI = 3.14159265359;

    printf("_______________________________\n");
    printf("|____x____|__sin x__|__cos x__|\n");

     for (x = 0; x <= 2 * PI; x = x + PI / 20) 
          printf("|__%+.3lf_|_%+.3lf__|_%+.3lf__|\n", x, sin(x), cos(x));

     printf("\n");

     return 0; 
}