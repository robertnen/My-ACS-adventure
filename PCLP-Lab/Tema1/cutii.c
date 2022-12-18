#include <stdio.h>

void readInput(int vector[], int* size); //citeste datele de intrare
//gaseste ciclurile
int findCycles(int boxes[], int cycles[], int positions[], short isOpen[], int size, int* lmax);
void output(int cycles[], int positions[], int numberOfCycles, short isWin);

int main() {

    // position tine minte numarul de pozitii
    int numberOfPrisoners, maxLength = -1, position, i;

    // positions retine unde incepe si unde se termina fiecare ciclu
    int boxes[501], cycles[501], positions[501];

    short isOpen[501], isWin; //tine minte ce cutii au fost deschide

    for(i = 0; i < 501; i++) isOpen[i] = 0;

    readInput(boxes, &numberOfPrisoners); 

    position = findCycles(boxes, cycles, positions, isOpen, numberOfPrisoners, &maxLength);

    isWin = maxLength <= numberOfPrisoners / 2;

    output(cycles, positions, position, isWin);

    return 0;
}

void readInput(int vector[], int* size) { //citeste datele de intrare

    int i;

    scanf("%d", size);
    for(i = 1; i <= (*size); i++) scanf("%d", &vector[i]);
}

//tine minte intr-un vector cycles toate ciclurile, iar in positions indicii
//de unde incep si se termina returneaza o valoarea egala
//cu 2 * numarul de cicluri pentru afisare
int findCycles(int boxes[], int cycles[], int positions[], short isOpen[], int size, int* lmax) {

    int iPos = 1, fPos = 1, numberOfCycles = 0, prisoner, i;

    for(i = 1; i <= size; i++) {
        if(!isOpen[i]) { //verific daca am mai fost

            //se incepe un ciclu nou si plec cu urmatorul element
            positions[++numberOfCycles] = iPos;
            prisoner = boxes[i];
            cycles[iPos] = i;

            while(!isOpen[prisoner]) {
                isOpen[prisoner] = 1;

                if(prisoner == i) { //s-a terminat ciclul
                    if((*lmax) < fPos - iPos + 1)
                        (*lmax) = fPos - iPos + 1;

                    //tin minte indexul din cycles unde se termina ciclul
                    positions[++numberOfCycles] = fPos;

                    //ipos are pozitia urmatorului ciclu (daca exista)
                    iPos = ++fPos;
                } else {

                    cycles[++fPos] = prisoner; //ciclul se mareste
                    prisoner = boxes[prisoner]; //merg mai departe
                }
            }
        }
    }
    return numberOfCycles;
}

void output(int cycles[], int positions[], int numberOfCycles, short isWin) {

    if(isWin) printf("Da\n"); //isWin semnifica daca prizonierii
    else printf("Nu\n"); //au castigat sau nu

    int iPos, fPos, i, j; //pozitia finala a unui ciclu, respectiv cea finala

    for(i = 1; i <= numberOfCycles; i += 2) {

        iPos = positions[i];
        fPos = positions[i + 1];

        //fac outputul ca sa mearga in checker
        printf("%d", cycles[iPos]);

        for(j = iPos + 1; j <= fPos; j++) printf(" %d", cycles[j]);
        printf("\n");
    }
}