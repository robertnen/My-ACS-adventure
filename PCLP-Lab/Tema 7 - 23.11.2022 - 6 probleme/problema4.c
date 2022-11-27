#include <stdio.h>
#include <string.h>

char* substr(char *src, int n, char *dest); // extrage de la pozitia src in dest n caractere

int main() {

    //declararea variabilelor
    char text[101], result[101];

    int a, b;

    //citirea
    fgets(text, 100, stdin);

    scanf("%d%d", &a, &b);

    //pun '\0'
    text[strlen(text) - 1] = '\0';
    
    //scot sirul
    substr(text + a, b, result);

    //result are in functie mai multe elemente decat ar trb sa aiba
    result[b] = '\0';

    //afisare
    printf("%s\n", result);

    return 0;

}

// extrage de la pozitia src in dest n caractere
char* substr(char *src, int n, char *dest) {

    strncpy(dest, src, n);

    return dest;

}

