#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void toLower(char string[]) {

    for(int index = 0; index < strlen(string); index++)
        if('A' <= string[index] && string[index] <= 'Z')
            string[index] += 32;
}

int main(int argc, char* argv[]) {

    FILE* fin;

    int index, counter = 0, lineCounter = 0, numberOfOp = 0;
    char input[1001], aux[1001], toFind[1001];
    bool isSensitive = true, isCounter = false, isLineCounter = false;

    fin = fopen(argv[argc - 2], "r");
    strcpy(toFind, argv[argc - 1]);

    if(!fin) {

        fprintf(stderr, "Eroare! Nu am putut deschide fisierul destinatie!\n");
        return 0;
    }

    if(argc < 3 || argc > 6){

        printf("Prea multe sau prea putine argumente!\n");
        return 0;
    }

    for(int index = 1; index < argc - 2; index++) {

        if(argv[index][0] == 'i') isSensitive = false;
        else if(argv[index][0] == 'c') isCounter = true;
             else if(argv[index][0] == 'n') isLineCounter = true;
    }


    while(fgets(input, 1000, fin) != NULL) {

        lineCounter++;

        strcpy(aux, input);

        if(!isSensitive) toLower(input);

        if(strstr(input, toFind) != NULL) {

            counter++;

            if(isLineCounter)
                printf("[%d] %s", lineCounter, aux);
            else printf("%s", aux);

        }
    }

    if(isCounter) printf("Numarul total de linii: %d\n", counter);

    fclose(fin);

    return 0;
}