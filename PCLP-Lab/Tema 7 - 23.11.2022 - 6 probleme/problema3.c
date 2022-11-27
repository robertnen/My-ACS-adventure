#include <stdio.h>
#include <string.h>
#include <stdbool.h>

char *strdel(char *p, int n); // sterge n caractere din pozitia p
char *strins(char *p, char *s); // insereaza la p, sirul s
//cauta un substring
int findPos(char* text, char* substring); 

int main() {

    char text[3000], aux[3000], toReplace[20], seq[20];

    int size, p;

    //citirea
    fgets(text, 3000, stdin);
    fgets(toReplace, 20, stdin);
    fgets(seq, 20, stdin);

    text[strlen(text) - 1] = '\0'; 
    toReplace[strlen(toReplace) - 1] = '\0'; 
    seq[strlen(seq) - 1] = '\0'; 

    //tin minte cat de lung e substringul
    size = strlen(toReplace);

    //am nevoie de o copie
    strcpy(aux, text);

    p = findPos(text, toReplace);

    //aici pun rezultatul
    strcpy(text, "");

        while(p != -1) {

           //tin minte ce era inainte de cuvant
           strncat(text, aux, p);

           //adaug cunvatul care e cerut
           strcat(text, seq);

           //merg mai departe de cuvantul ce este schimbat
           strcpy(aux, aux + p + size);

           //verific daca mai exista astfel de substringuri
           p = findPos(aux, toReplace);

        } 

    printf("%s", text);

    return 0;

}

char *strdel(char *p, int n) {

    strcpy(p, p + n);

    return p;

}

char *strins(char *p, char *s) {

    char aux[3001];

    strcpy(aux, s);

    strcat(aux, p);

    strcpy(p, aux);

    return p;
}

int findPos(char* text, char* substring) {

    char *p;

    for(int i = 0; i <= strlen(text); i++){

        //verific daca e substring
        if(text[i] == substring[0]) {

            strncpy(p, text + i, strlen(substring) - 1);

            //este substring
            if(strcmp(p, substring) == 0) {return i;}

        } 

    }

    //nu este
    return -1;

}