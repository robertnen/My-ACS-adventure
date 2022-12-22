#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]) {

    FILE* fin;

    fin = fopen(argv[1], "r");

    int index;
    char input[1001], toFind[1001];

    if(!fin) {

        fprintf(stderr, "Eroare! Nu am putut deschide fisierul destinatie!\n");
        return 0;
    } 

    strcpy(toFind, argv[2]);

    while(fgets(input, 1000, fin) != NULL) {

        if(strstr(input, toFind) != NULL)
            printf("%s", input);
    }


    fclose(fin);

    return 0;
}