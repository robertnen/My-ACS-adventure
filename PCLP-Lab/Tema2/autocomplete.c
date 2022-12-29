#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct dictionary_entry {

    char* word;
    int priority;
};

//ca sa nu depasesc 80 de caractere / linie
typedef struct dictionary_entry entry_t;

//aici se baga cuvintele primite la inceput in dictionar
void getDictionaryWords(int numberOfWords, entry_t* words);
//sortez cuvintele lexicografic
void dictionarySort(int numberOfWords, entry_t* words);
//returneaza pe ce pozitie se afla un cuvant, -1 daca nu exista
int getWordIndex(int numberOfWords, entry_t* words, char word[]);
int hasAsterisk(char word[]);
//verific daca cuvantul este ,.:!? sau contine litere
int isWord(char word[]);
//verific daca toCheck e prefix
int isPrefix(char word[], char toCheck[]);
//returneaza pozitia cuvantului cautat sau -1 daca nu exista
int findWord(int numberOfWords, entry_t* words, char prefix[]);
//adaug un cuvant in dictionar
entry_t* addWordInDictionary(int* n, entry_t* words, char word[]);

int main() {

    entry_t *words;

    int n, m, index, isAlready, jndex;
    char aux[21];

    scanf("%d", &n);

    words = malloc(n * sizeof(entry_t));

    getDictionaryWords(n, words);
    dictionarySort(n, words);

    scanf(" %d", &m);

    for(index = 0; index < m; index++) {

        scanf(" %s", aux);

        if(hasAsterisk(aux)) { //cuvant nou probabil

            aux[strlen(aux) - 1] = '\0';
            isAlready = 0;

            for(jndex = 0; jndex < n; jndex++)
                if(!strcmp((words + jndex)->word, aux)) {

                    isAlready = 1; //deja exista cuvantul
                    break;
                }

            if(!isAlready) words = addWordInDictionary(&n, words, aux);
            else (words + jndex)->priority++;

            printf("%s ", aux);
        } else {

            if(!isWord(aux)) {  //"cuvantul" este , . ? : etc

                printf("%s ", aux);
                continue;
            }
            if(findWord(n, words, aux) == -1) { //cuvantul nu exista

                printf("%s ", aux);
                words = addWordInDictionary(&n, words, aux);

            } else {
                printf("%s ", (words + findWord(n, words, aux))->word);
                (words + findWord(n, words, aux))->priority++;
            }
        }
    }

    for(index = 0; index < n; index++) //eliberarea memoriei
        free((words + index)->word);

    free(words);
    return 0;
}

//aici se baga cuvintele primite la inceput in dictionar
void getDictionaryWords(int numberOfWords, entry_t* words) {

    char word[21];
    int index;

    for(index = 0; index < numberOfWords; index++) {

        scanf(" %s", word);

        (words + index)->word = (char*) calloc(strlen(word) + 1, sizeof(char));
        strcpy((words + index)->word, word);
        (words + index)->priority = 0;
    }
}

//sortez cuvintele lexicografic
void dictionarySort(int numberOfWords, entry_t* words) {

    int isSorted = 0, i, size;
    char aux_1[21], aux_2[21];

    while(!isSorted) {

        isSorted = 1;

        for(i = 0; i < numberOfWords - 1; i++)
            if(strcmp((words + i)->word, (words + i + 1)->word) > 0) {

                strcpy(aux_1, (words + i)->word);
                strcpy(aux_2, (words + i + 1)->word);

                free((words + i)->word); free((words + i + 1)->word);

                size = strlen(aux_2) + 1;
                (words + i)->word = (char*) calloc(size, sizeof(char));

                size = strlen(aux_1) + 1;
                (words + i + 1)->word = (char*) calloc(size, sizeof(char));

                strcpy((words + i)->word, aux_2);
                strcpy((words + i + 1)->word, aux_1);

                isSorted = 0;
            }
    }
}

//returneaza pe ce pozitie se afla un cuvant, -1 daca nu exista
int getWordIndex(int numberOfWords, entry_t* words, char word[]) {

    int index;
    for(index = 0; index < numberOfWords; index++)
        if(!strcmp((words + index)->word, word)) return index;

    return -1;
}

int hasAsterisk(char word[]) {

    if(word[strlen(word) - 1] == '*') return 1;
    return 0;
}

//verific daca cuvantul este ,.:!? sau contine litere
int isWord(char word[]) {

    if((strlen(word) == 1 && word[0] < 'a') || word[0] > 'z') return 0;
    return 1;
}

//verific daca toCheck e prefix
int isPrefix(char word[], char toCheck[]) {

    int index;
    if(strlen(word) < strlen(toCheck)) return 0; //cuvant prea mic

    for(index = 0; index < strlen(toCheck); index++)
        if(word[index] != toCheck[index]) return 0;

    return 1;
}

//returneaza pozitia cuvantului cautat sau -1 daca nu exista
int findWord(int numberOfWords, entry_t* words, char prefix[]) {

    int index, maxPriority = 0, position = -1;

    for(index = numberOfWords - 1; index > -1; index--)
        if(isPrefix((words + index)->word, prefix))
            if(maxPriority <= (words + index)->priority) {

                maxPriority = (words + index)->priority;
                position = index;
            }

    return position;
}

//adaug un cuvant in dictionar
entry_t* addWordInDictionary(int* n, entry_t* words, char word[]) {

    int pos = 0, i, size;
    //pozitia unde va fi noul cuvant
    while(pos < (*n) && strcmp((words + pos)->word, word) < 0) pos++;

    entry_t* tmp;
    tmp = (entry_t*) malloc(((*n) + 1) * sizeof(entry_t));

    for(i = 0; i < pos; i++) {

        size = strlen((words + i)->word) + 1;
        (tmp + i)->priority = (words + i)->priority;

        (tmp + i)->word = (char*) calloc(size , sizeof(char));
        strcpy((tmp + i)->word, (words + i)->word);
    } //copiez cuvintele pana la position exact cum erau

    (tmp + pos)->word = (char*) calloc((strlen(word) + 1), sizeof(char));
    (tmp + pos)->priority = 1; //cel nou

    strcpy((tmp + pos)->word, word);

    for(i = pos + 1; i <= (*n); i++) {

        size = strlen((words + i - 1)->word) + 1;
        (tmp + i)->priority = (words + i - 1)->priority;

        (tmp + i)->word = (char*) calloc(size, sizeof(char));
        strcpy((tmp + i)->word, (words + i - 1)->word);
    } //duc cu un indice mai in fata restul

    for(i = 0; i < (*n); i++)
        free((words + i)->word);

    free(words);
    (*n)++;
    return tmp;
}