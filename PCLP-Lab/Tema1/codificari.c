#include <stdio.h>
#include <string.h>

void readString(char *p, int size); //citeste un string
int charToIntNumber(char* number); // transforma din char in int un numar
void codificareB(char* text, int key);
void decodificareB(char* text, int key);
void codificareA(char* text, char* word);
void decodificareA(char* text, char* word);
//primeste ca input o linie si furnizeaza operatia si cheia
void getWords(char* text, char* type, char* key);

int main() {

    char text[500], line[500], operation[15], key[50];

    readString(text, 500);
    readString(line, 500);

    while(strcmp(line, "STOP")) {

        getWords(line, operation, key); //tin minte operatia si cheia

        if(!strcmp(operation, "CodificareA")) codificareA(text, key);
        else if(!strcmp(operation, "CodificareB"))
                    codificareB(text, charToIntNumber(key));
               else if(!strcmp(operation, "DecodificareA"))
                        decodificareA(text, key);
                    else decodificareB(text, charToIntNumber(key));

        printf("%s\n", text);
        readString(line, 500);
    }

    return 0;

}

void readString(char *p, int size) { //citeste un string

    fgets(p, size, stdin);
    p[strlen(p) - 1] = '\0';

}

int charToIntNumber(char* number) { // transforma din char in int un numar

    int result = 0, i;

    for(i = 0; i < strlen(number); i++) 
        result = result * 10 + number[i] - '0';

    return result;
}

void codificareB(char* text, int key) {

    char p[500], q[500], letters[52];
    int i, aux;

    strcpy(p, text + strlen(text) - key); //in p e ce va fi la inceput
    strncpy(q, text, strlen(text) - key); //in q ce ramane

    q[strlen(text) - key] = '\0';

    aux = strlen(text) - key;

    strcpy(text, text + aux);

    for(i = 0; i < 26; i++)
        letters[i] = 'A' + i;

    for(i = 26; i < 52; i++)
        letters[i] = 'a' + i - 26;

    key = key % 52; //perioada

    for(i = 0; i < strlen(p); i++) //adun fiecare caracter cu key
        if(p[i] >= 'a' && p[i] <= 'z') {

            aux = (int)(p[i] - 'a') + 26;

            aux += key;

            aux = aux % 52;

            p[i] = letters[aux];

        } else if(p[i] >= 'A' && p[i] <= 'Z'){

            aux = (int)(p[i] - 'A') + key;

            aux = aux % 52;

            p[i] = letters[aux];

            }

    strcat(p, q); //am obtinut codificareB
    strcpy(text, p);
    text[strlen(text)] = '\0'; //aparent nu merge fara asta

}

void decodificareB(char* text, int key) {

    char p[500], q[500], letters[52];
    int i, aux, length = strlen(text);

    strcpy(q, text + key); //in q e ce va fi la inceput
    strncpy(p, text, key); //in p iau ce va fi decriptat

    q[strlen(text) - key] = '\0';

    key = key % 52; //perioada

    for(i = 0; i < 26; i++)
        letters[i] = 'A' + i;

    for(i = 26; i < 52; i++)
        letters[i] = 'a' + i - 26;

    for(i = 0; i < strlen(p); i++)  //decripatare
        if(p[i] >= 'a' && p[i] <= 'z') {

            aux = (int)(p[i] - 'a') + 26 - key;

            if(aux < 0) aux = 52 + aux;

            aux = aux % 52;

            p[i] = letters[aux];

        } else if(p[i] >= 'A' && p[i] <= 'Z') {

                     aux = (int)(p[i] - 'A') - key;

                    if(aux < 0) aux = 52 + aux;

                    p[i] = letters[aux];
            }

    strcat(q, p); //am obtinut decodificarea
    strcpy(text, q);
    text[length] = '\0'; //aparent si aici trebuie asta

}

void codificareA(char* text, char* word) {

    char ctc[501][50], blankSpace[50], auxC;
    int size = strlen(text), r, aux, permutation[50];
    int i, j, length = strlen(word); //lungimea cuvantului-cheie
    short isSorted = 0;

    for(i = 0; i < length; i++)
        blankSpace[i] = ' '; //initializez vectorul cu caractere ' '

    blankSpace[length] = '\0';

    for(i = 1; i <= size / length + 1; i++)
        strcpy(ctc[i], blankSpace); //matricea contine la inceput ' '

     for(i = 0; i < size; i++)
         ctc[i / length + 1][i % length] = text[i];

    for(i = 0; i < length; i++) permutation[i] = i; //permutarea identica

    while(!isSorted) {

        isSorted = 1;

        for(i = 0; i < length - 1; i++) {

            j = i + 1;

            while(j < length) {
                if(word[j] < word[i]) {

                    isSorted = 0;
                    auxC = word[i]; word[i] = word[j]; word[j] = auxC;
                    aux = permutation[i];
                    permutation[i] = permutation[j]; 
                    permutation[j] = aux;
            
                    break;
                }
            j++;
            }
        }
    }

    strcpy(ctc[0], word);

    //daca se intampla ca size / length sa fie intreg, matricea 
    //are toate elementele modificate, deci nu voi avea o linie in plus
    if(size % length == 0) r = 0;
    else r = 1;

    aux = 0;

    for(i = 0; i < length; i++) //bag in txt codificareA
        for(j = 1; j <= size / length + r; j++)
            text[aux++] = ctc[j][permutation[i]];

    text[aux] = '\0';
}

void decodificareA(char* text, char* word) {

    char dtc[501][50], blankSpace[50], auxC;
    int size = strlen(text), r, aux, row, col;
    int permutation[50], positions[50]; //ma ajuta la decodificare
    int i, j, length = strlen(word); //cuvantul-cheie
    short isSorted = 0;

    for(i = 0; i < length; i++)
        blankSpace[i] = ' '; //initializez vectorul cu caractere ' '

    blankSpace[length] = '\0';

    for(i = 1; i <= size / length + 1; i++)
        strcpy(dtc[i], blankSpace); //matricea contine la inceput ' '

    //daca se intampla ca size / length sa fie intreg, matricea
    //are toate elementele modificate, deci nu voi avea o linie in plus
    if(size % length == 0) r = 0;
    else r = 1;

    row = col = 0;

    for(i = 0; i < size; i++) {

        dtc[++row][col] = text[i];
        if(r + size / length == row) {

            row = 0;
            ++col;
        }
    }

    for(int i = 0; i < length; i++) permutation[i] = i; //permutarea identica

    strcpy(blankSpace, word);

    while(!isSorted) {

        isSorted = 1;

        for(i = 0; i < length - 1; i++) {

            j = i + 1;

            while(j < length) {
                if(word[j] < word[i]) {

                    isSorted = 0;
                    auxC = word[i]; word[i] = word[j]; word[j] = auxC;
                    aux = permutation[i]; 
                    permutation[i] = permutation[j];
                    permutation[j] = aux;
            
                    break;
                }
            j++;
            }
        }
    }

    for(i = 0; i < length; i++) positions[permutation[i]] = i;

    strcpy(dtc[0], word);

    aux = 0;

    for(j = 1; j <= size / length + r; j++)
        for(i = 0; i < length; i++) //bag in txt codificareA
            text[aux++] = dtc[j][positions[i]];
    
    text[aux] = '\0';
}

//primeste ca input o linie si furnizeaza operatia si cheia
void getWords(char* text, char* type, char* key) {

        char* p = strtok(text, " "), q[51];

        strcpy(type, p);   //copiez operatia

        p = strtok(NULL, " ");

        strcpy(q, "");

        while(p != NULL) { //formez cheia

            strcat(q, p);
            strcat(q, " ");

            p = strtok(NULL, " ");
        }

        q[strlen(q) - 1] = '\0';

        strcpy(key, q); //copiez cheia
}