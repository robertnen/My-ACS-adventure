#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct {

    char** words;
    int* pos; //unde incep cuvintele
    int count; //numarul de cuvinte (nu trebuie sa fie distincte)

} Line;

//citeste o linie, o imparte in cuvinte si tine minte undese afla fiecare
int readLine(Line* line, char lineInput[]);
//functia returneaza pozitia pe care o are keyword-ul sau -1 daca nu este
int wordPosition(char* word);
//pune _ de la pos_1 la pos_2 inclusiv
void modifyLine(char outputLine[], int pos_1, int pos_2);
//aici se rezolva in principal exercitiul prin verificarea cuvintelor
void outputPerLine(Line* line, int size, char output[]);

int main() {

    int n, index, length;
    char output[100] = "", lineInput[100] = "";
    Line line;

    scanf("%d ", &n);

    line.words = (char**) malloc(100 * sizeof(char*));
    line.pos = (int*) calloc(100, sizeof(int));

    for(index = 0; index < 100; index++)
        line.words[index] = (char*) calloc(100, sizeof(char));

    for(index = 0; index < n; index++) {

        //iau linie cu linie, scot in line cuvintele si pozitia fiecaruia
        //si in length pun lungimea liniei citite
        length = readLine(&line, lineInput);

        outputPerLine(&line, length, output);
        output[length + 1] = '\0'; //ca sa fac outputul corect
        printf("%s\n%s\n", lineInput, output);

    }

    for(index = 0; index < 100; index++)  //eliberez spatiul
        free(line.words[index]);

    free(line.pos);
    free(line.words);
    return 0;
}

//citeste o linie, o imparte folosind strtok in cuvinte si tine minte unde
//se afla fiecare
int readLine(Line* line, char lineInput[]) {

    char input[103], *p;

    fgets(input, 103, stdin); //unele teste au si 102 caractere pe un rand...

    input[strlen(input) - 1] = '\0';
    int length = strlen(input) - 1;

    strcpy(lineInput, input); //de asta am nevoie la output

    ptrdiff_t diff_index; //pentru a calcula indexul cuvintelor

    line->count = 0;
    p = strtok(input, " ");

    while(p != NULL) {

        diff_index = p - input;

        line->pos[++line->count] = (int)diff_index;
        strcpy(line->words[line->count], p); //tin minte si cuvantul

        p = strtok(NULL, " ");
    }

    return length;
}

//functia returneaza pozitia pe care o are keyword-ul sau -1 daca nu este
int wordPosition(char* word) {

    const char KEYWORDS[15][11] = {
                                    "first of", "is a", "list of", "for each",
                                    "from", "in", "is", "for", "unit", "or",
                                    "while", "int", "float", "double", "string"
                                  };
    for(int i = 0; i < 15; i++)
        if(!strcmp(word, KEYWORDS[i])) return i;

    return -1;

}

//pune _ de la pos_1 la pos_2 inclusiv
void modifyLine(char outputLine[], int pos_1, int pos_2) {

    for(int i = pos_1; i <= pos_2; i++) outputLine[i] = '_';
}

//aici se rezolva in principal exercitiul prin verificarea cuvintelor
void outputPerLine(Line* line, int size, char output[]) {

    int pos;

    for(int i = 0; i <= size; i++) output[i] = ' ';

    for(int i = 0; i <= line->count; i++) {

        if(wordPosition(line->words[i]) > -1) { //keyword dintr-un cuvant

            pos = line->pos[i] + strlen(line->words[i]) - 1;
            modifyLine(output, line->pos[i], pos);

            if(!strcmp(line->words[i], "for")) {

                if(i < line->count && !strcmp(line->words[i + 1], "each"))
                    modifyLine(output, line->pos[i], line->pos[i + 1] + 3);

            } else if(!strcmp(line->words[i], "is")) {

                        if(i < line->count && !strcmp(line->words[i + 1], "a"))
                            modifyLine(output, line->pos[i], line->pos[i + 1]);

                    } else {
                        pos = line->pos[i] + strlen(line->words[i]) - 1;
                        modifyLine(output, line->pos[i], pos);
                    }
        }

        //verific daca apare combinatie de doua keyword-uri
        if(!strcmp(line->words[i], "first"))
            if(i < line->count && !strcmp(line->words[i + 1], "of"))
                    modifyLine(output, line->pos[i], line->pos[i + 1] + 1);

        if(!strcmp(line->words[i], "list"))
            if(i < line->count && !strcmp(line->words[i + 1], "of"))
                    modifyLine(output, line->pos[i], line->pos[i + 1] + 1);
    }
}