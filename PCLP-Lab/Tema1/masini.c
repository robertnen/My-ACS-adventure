#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct CD{

    char** brands, **numbers, **types;
    double* consumptions, *totalConsumptions, *price;
    int* kms, *index, size, benzina, motorina, hibrid, electric;
    short* isValidPlates;

} CarDealership; //l-am facut ca sa nu folosesc prea multi parametri

//transforma un vector char intr-un numar de tip int
int charToIntNumber(char toConvert[]); 
//transforma un vector char intr-un numar de tip double
double charToDoubleNumber(char toConvert[]); 
//scoate informatiile unei masini
void getInfo(char textLine[], char brand[], char number[], char carType[], double* consumption, int* km);
void readingInput(CarDealership* dealer, int* size, char* task);
//aflu cate masini merg pe fiecare tip de combustibil
void taskA(CarDealership* dealer, int size); 
//aflu consumul si pretul
void taskB(CarDealership* dealer, int size); 
//verific care numere sunt corecte
void taskC(CarDealership* dealer, int size); 

int main() {

    CarDealership dealer;
    int size, i;
    long int aprox;
    char task;

    readingInput(&dealer, &size, &task);

    if(task == 'a') {

        dealer.hibrid = 0;
        dealer.benzina = 0;
        dealer.electric = 0;
        dealer.motorina = 0;

        taskA(&dealer, size);
        printf("benzina - %d\nmotorina - %d\nhibrid - %d\nelectric - %d\n", dealer.benzina, dealer.motorina, dealer.hibrid, dealer.electric);

    } else if(task == 'b') {

            taskB(&dealer, size);

            for(i = 0; i < size; i++) //consumul total al unui brand
                    if(dealer.index[i]) {
                   
                    aprox = dealer.totalConsumptions[i] * 1000000;

                    if(aprox % 100 == 99) aprox += 1; //ca sa nu pierd precizia

                    dealer.totalConsumptions[i] = (double)(aprox / 1000000.);

                    printf("%s a consumat %.2lf - %.2lf lei\n", dealer.brands[i], dealer.totalConsumptions[i], dealer.price[i]);

                }

            //eliberez memoria ca nu imi mai trebuie
            free(dealer.price);
            free(dealer.index); free(dealer.totalConsumptions);

        } else {

                short isOk = 1;
                taskC(&dealer, size);

                for(i = 0; i < size; i++) {
                    if(!dealer.isValidPlates[i]) { //numarul nu e valid

                        printf("%s cu numarul %s: numar invalid\n", dealer.brands[i], dealer.numbers[i]);
                        isOk = 0; //nu sunt toate corecte
                    }
                }

                if(isOk) printf("Numere corecte!\n");

                //eliberez memoria pt ca nu mai am nevoie
                free(dealer.isValidPlates);
            }

    for(i = 0; i < size; i++) { //eliberez memoria

        free(dealer.types[i]);
        free(dealer.brands[i]);
        free(dealer.numbers[i]);
    }

    free(dealer.types);
    free(dealer.brands);
    free(dealer.numbers);
    free(dealer.consumptions); 
    free(dealer.kms);

    return 0;
}

//transforma un vector char intr-un numar de tip int
int charToIntNumber(char toConvert[]) { 

    int result = 0, i;

    for(i = 0; i < strlen(toConvert); i++) result = 10 * result + toConvert[i] - '0';
    return result;
}

//transforma un vector char intr-un numar de tip double
double charToDoubleNumber(char toConvert[]) {

    double result = 0;
    int powerOfTen = 1, i;
    short isAfterPoint = 0; //verifica daca am avut punct 

    for(i = 0; i < strlen(toConvert); i++) {
        if(toConvert[i] == '.') isAfterPoint = 1;
        else if(isAfterPoint) {

                powerOfTen *= 10; //pentru urmatoarea zecimala
                result = result + (double)(toConvert[i] - '0') / powerOfTen;

            } else result = result * 10 + toConvert[i] - '0';
    }
    return result;
}

//scoate informatiile unei masini
void getInfo(char textLine[], char brand[], char number[], char carType[], double* consumption, int* km) {

        char* p = strtok(textLine, " "), aux[30];

        strcpy(brand, p); p = strtok(NULL, " ");
        strcpy(number, p); p = strtok(NULL, " ");
        strcpy(carType, p); p = strtok(NULL, " ");

        strcpy(aux, p); p = strtok(NULL, " ");
        (*consumption) = charToDoubleNumber(aux);

        strcpy(aux, p);
        (*km) = charToIntNumber(aux);
}

void readingInput(CarDealership* dealer, int* size, char* task) {

    char lineInput[50]; //cu ea citesc fiecare linie doar
    int i;

    scanf("%d ", size); //citesc numarul de masini

    dealer->consumptions = (double*) calloc((*size), sizeof(double)); //alocarea dinamica
    dealer->kms = (int*) calloc((*size), sizeof(int));

    dealer->types = (char**) malloc((*size) * sizeof(char*));
    dealer->brands = (char**) malloc((*size) * sizeof(char*));
    dealer->numbers = (char**) malloc((*size) * sizeof(char*));

    for(i = 0; i < (*size); i++) {

        dealer->types[i] = (char*) calloc(30, sizeof(char));
        dealer->brands[i] = (char*) calloc(30, sizeof(char));
        dealer->numbers[i] = (char*) calloc(30, sizeof(char));

    }

    for(i = 0; i < (*size); i++) {

        //scrie ca un rand are 20 de caractere in enunt
        //dar in teste am gasit si cu 42...
        fgets(lineInput, 50, stdin); 
        lineInput[strlen(lineInput) - 1] = '\0';

        getInfo(lineInput, dealer->brands[i], dealer->numbers[i], dealer->types[i], &dealer->consumptions[i], &dealer->kms[i]);
    }
    scanf("%c", task);
}

void taskA(CarDealership* dealer, int size) { //aflu cate masini merg pe fiecare tip de combustibil

    int i;

    for(i = 0; i < size; i++)
        if(!strcmp(dealer->types[i], "benzina")) dealer->benzina++;
            else if(!strcmp(dealer->types[i], "motorina")) dealer->motorina++;
                 else if(!strcmp(dealer->types[i], "hibrid")) dealer->hibrid++;
                      else dealer->electric++;
}

void taskB(CarDealership* dealer, int size) { //aflu consumul si pretul

    int i, j;

    //in el tin minte daca am adaugat masina la consumul brandului sau
    dealer->index = (int*) calloc(size, sizeof(int));

    //in el tin minte daca am adaugat masina la brandul sau
    dealer->totalConsumptions = (double*) calloc(size, sizeof(double));

    //in el tin minte pretul
    dealer->price = (double*) calloc(size, sizeof(double));

    short* isUnique = (short*) calloc(size, sizeof(short));

    for(i = 0; i < size; i++) {
        
        for(j = i + 1; j < size && !isUnique[i]; j++) {
            if(!strcmp(dealer->brands[i], dealer->brands[j]) && !isUnique[j]) {

                isUnique[j] = 1;

                dealer->totalConsumptions[i] += (dealer->consumptions[j] * dealer->kms[j] / 100.0);

                if(!strcmp(dealer->types[j], "benzina") || !strcmp(dealer->types[j], "hibrid"))
                        dealer->price[i] += (dealer->consumptions[j] * dealer->kms[j] / 100.0 * 8.02);

                    else if(!strcmp(dealer->types[j], "motorina"))
                        dealer->price[i] += (dealer->consumptions[j] * dealer->kms[j] / 100.0 * 9.29);
            }
        }

        if(!isUnique[i]) {

            dealer->index[i] = i + 1;

            isUnique[i] = 1;

            dealer->totalConsumptions[i] += (dealer->consumptions[i] * dealer->kms[i] / 100.0);

            if(!strcmp(dealer->types[i], "benzina") || !strcmp(dealer->types[i], "hibrid"))
                        dealer->price[i] += (dealer->consumptions[i] * dealer->kms[i] / 100.0 * 8.02);

                    else if(!strcmp(dealer->types[i], "motorina"))
                        dealer->price[i] += (dealer->consumptions[i] * dealer->kms[i] / 100.0 * 9.29);
        }
    }
    free(isUnique);
}

//verific care numere sunt corecte
void taskC(CarDealership* dealer, int size) {

    dealer->isValidPlates = (short*) calloc(size, sizeof(short));
    char aux[50]; //ca sa fie mai usor de citit
    int length, i;

    for(i = 0; i < size; i++) {

        strcpy(aux, dealer->numbers[i]);

        length = strlen(aux);

        //poate fi de forma LCCCLLL, LCCLLL, LLCCCLLL sau LLCCLLL
        if(length < 6 || length > 8)
            continue;  //numar invalid, merg mai departe, nu are sens
        else {         //sa continui deoarece implicit e false

            //verific daca ultimele 3 caractere sunt litere
            if(aux[length - 1] < 'A' || aux[length - 1] > 'Z') continue;
            if(aux[length - 2] < 'A' || aux[length - 2] > 'Z') continue;
            if(aux[length - 3] < 'A' || aux[length - 3] > 'Z') continue;

            if(aux[0] < 'A' || aux[0] > 'Z') continue;

            //e de forma LCXLLL sau LCXYLLL, unde X si Y pot fi L sau C
            if(aux[1] >= '0' && aux[1] <= '9') {

                    if(length == 6 && aux[2] >= '0' && aux[2] <= '9')
                        dealer->isValidPlates[i] = 1;

                    else if(length == 7 && aux[2] >= '0' && aux[2] <= '9' && aux[3] >= '0' && aux[3] <= '9')
                            dealer->isValidPlates[i] = 1;

                        //nu exista alte cazuri care au o litera la inceput
                         else continue;

            //e de forma LLCXLLL sau LLCXYLLL, unde X si Y pot fi L sau C
            } else if(aux[2] >= '0' && aux[2] <= '9') {

                    if(length == 7 && aux[3] >= '0' && aux[3] <= '9')
                        dealer->isValidPlates[i] = 1;

                    else if(length == 8 && aux[3] >= '0' && aux[3] <= '9' && aux[4] >= '0' && aux[4] <= '9')
                            dealer->isValidPlates[i] = 1;

                        //nu exista alte cazuri care au doua litere la inceput
                         else continue;

                } else continue;
        }
    }
}