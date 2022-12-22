#include <stdio.h>
#include <string.h>

typedef struct {

    char toConvert;
    char converted;

} Conversion;

int main(int argc, char* argv[]) {

    FILE* fin, *fin_2, *fout;
    Conversion tabel[100];

    fin = fopen(argv[1], "r");
    fin_2 = fopen(argv[2], "r");
    fout = fopen(argv[3], "w");

    if(!fin || !fin_2 || !fout) {

        fprintf(stderr, "Eroare! Nu am putut deschide fisierul destinatie!\n");
        return 0;
    }

    char input[1001];
    int counter = 0;

    while(fgets(input, 1000, fin) != NULL) {

        tabel[counter].toConvert = input[0];
        tabel[counter++].converted = input[2];
    }

    fclose(fin);

    while(fgets(input, 1000, fin_2) != NULL) {

        for(int index = 0; index < strlen(input); index++) {

            for(int jndex = 0; jndex <= counter; jndex++)
                if(input[index] == tabel[jndex].toConvert) {

                    input[index] = tabel[jndex].converted;
                    break;
                
                } else if(input[index] == tabel[jndex].toConvert - 32) {

                        input[index] = tabel[jndex].converted - 32;
                        break;
                }
        }

        fputs(input, fout);
    }

    fclose(fin_2);
    fclose(fout);

    return 0;
}