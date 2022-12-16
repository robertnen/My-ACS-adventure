#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Pereche {

    char* word;
    int count;

}Pair;

void metodaI();
void metodaII();

int main() {

    Pair pair;
    char input[100] = "", aux[100], auxInput[100], **words;
    int n, *count;

    scanf("%d", &n);

    for(int i = n; i > 0; i--) {

        scanf(" %s", aux);

        strcat(input, aux);
        strcat(input, " ");
    }

    input[strlen(input) - 1] = '\0'; //inputul

    strcpy(auxInput, input);

    metodaI(input, words, count);

    printf("\n"); // ca sa se vada si metoda a II-a

    metodaII(&pair, auxInput);

    return 0;
}

void metodaI(char* input, char** words, int* count) {

    char aux[100], *p;
    int pos, numberOfWords;
    bool isAlready;

    words = (char**) malloc((strlen(input) - 1) * sizeof(char*));
    count = (int*) calloc((strlen(input) - 1), sizeof(int));

    for(int i = 0; i < strlen(input); i++)
        words[i] = (char*) calloc(strlen(input) - 1, sizeof(char));

    p = strtok(input, " ");

    numberOfWords = 0;

    while(p != NULL) {

        strcpy(aux, p);

        isAlready = false;

        for(int i = 0; i < numberOfWords; i++)
            if(!strcmp(aux, words[i])) {

                isAlready = true;
                pos = i;
                break;
            }
        
        if(isAlready) count[pos]++;
        else {

            strcpy(words[numberOfWords], aux);
            count[numberOfWords++]++;
        }

        p = strtok(NULL, " ");
    }

    for(int i = 0; i < numberOfWords; i++)
        printf("%s %d\n", words[i], count[i]);

    for(int i = 0; i < strlen(input); i++)
        free(words[i]);

    free(words);
    free(count);
}

void metodaII(Pair* pair, char* input) {

    char aux[100], *p;
    int pos, numberOfWords;
    bool isAlready;

    pair = (Pair*) malloc((strlen(input) - 1) * sizeof(Pair));

    for(int i = 0; i < strlen(input); i++) {
        
        (pair + i)->word = (char*) calloc((strlen(input) - 1), sizeof(char));
        (pair + i)->count = 0;
    }

    p = strtok(input, " ");

    numberOfWords = 0;

    while(p != NULL) {

        strcpy(aux, p);

        isAlready = false;

        for(int i = 0; i < numberOfWords; i++)
            if(!strcmp(aux, (pair + i)->word)) {

                isAlready = true;
                pos = i;
                break;
            }
        
        if(isAlready) (pair + pos)->count++;
        else {

            strcpy((pair + numberOfWords)->word, aux);
            (pair + numberOfWords)->count++;
            numberOfWords++;
        }

        p = strtok(NULL, " ");
    }

    for(int i = 0; i < numberOfWords; i++)
        printf("%s %d\n", (pair + i)->word, (pair + i)->count);

    for(int i = 0; i < strlen(input); i++) {
        free((pair + i)->word);

    }
}