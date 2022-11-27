#include <stdio.h>
#include <string.h>

//comapara doua siruri
int stringCompare(char string_1[], char string_2[], int size_1, int size_2);

int main() {

    char s1[101], s2[101];

    //citirea
    scanf("%s", s1);
    scanf("%s", s2);

    //afisare
    printf("%d", stringCompare(s1, s2, strlen(s1), strlen(s2)));

    return 0;

}

//comapara doua siruri
int stringCompare(char string_1[], char string_2[], int size_1, int size_2) {

    //returnez valoarea in int a caracterelor care fac diferenta intre siruri

    //nu sunt siruri egale ca lungime
    if(size_1 < size_2) return -1;
    else if(size_1 > size_2) return -1;

    //verific daca sunt egale
    for(int i = 0; i < size_1; i++)
        if(string_1[i] != string_2[i]) {

            //verific care caracter e mai mare
            if(string_1[i] < string_2[i]) return -1;
            else return 1;

        }

    //sunt egale
    return 0;
}