#include <stdio.h>
#include <stdbool.h>

//citeste datele de intrare
void readInput(int vector[], int* size);

//tine minte intr-un vector cycles toate ciclurile, iar in positions indicii de unde incep si se termina
//returneaza o valoarea egala cu 2 * numarul de cicluri pentru afisare
int findCycles(int boxes[], int cycles[], int positions[], bool isOpen[], int size, int* lmax);

//afisarea - isWin semnifica daca prizonierii au castigat sau nu
void output(int cycles[], int positions[], int numberOfCycles, bool isWin);

int main() {

    int numberOfPrisoners, maxLength, position, index;

    //boxes -> pt cutii; cycles -> tine minte toate ciclurile;
    // positions -> retine in cycles unde incepe si unde se termina un ciclu
    int boxes[501], cycles[501], positions[501];

    //tine minte ce cutii au fost deschide
    bool isOpen[501] = {0};

    readInput(boxes, &numberOfPrisoners);
    
    maxLength = -1;

    position = findCycles(boxes, cycles, positions, isOpen, numberOfPrisoners, &maxLength);


    printf("%d", maxLength);

    printf("\n");

    for(int i = 1; i <= position; i++)
        printf("%d ", positions[i]);

    printf("\n");

    for(int i = 1; i <= numberOfPrisoners; i++)
        printf("%d ", cycles[i]);
    

    //output(cycles, positions, position, (maxLength <= numberOfPrisoners / 2));

    return 0;
}

//citeste datele de intrare
void readInput(int vector[], int* size) {

    scanf("%d", size);

    for(int i = 1; i <= (*size); i++)
        scanf("%d", &vector[i]);
    
}

//tine minte intr-un vector cycles toate ciclurile, iar in positions indicii de unde incep si se termina
//returneaza o valoarea egala cu 2 * numarul de cicluri pentru afisare
int findCycles(int boxes[], int cycles[], int positions[], bool isOpen[], int size, int* lmax) {

    int iPos, fPos, numberOfCycles, prisoner;

    numberOfCycles = 1;
    iPos = fPos = 1;

    for(int i = 1; i <= size; i++) {

        if(!isOpen[i]) {

            printf("Prisoner: %2d iPos: %2d\n", i, iPos);

            positions[numberOfCycles] = iPos;
            prisoner = i;
            cycles[iPos] = i;

            while(!isOpen[prisoner]) {

                isOpen[prisoner] = true;

                if(prisoner == i) {
                    

                    if((*lmax) < fPos - iPos + 1) (*lmax) = fPos - iPos + 1;

                    positions[++numberOfCycles] = fPos;
                    iPos = fPos + 1;

                } else {

                    cycles[++fPos] = prisoner;
                    prisoner = boxes[prisoner];

                }

            }

        }

    }
    
    return numberOfCycles;
}

//afisarea - isWin semnifica daca prizonierii au castigat sau nu
void output(int cycles[], int positions[], int numberOfCycles, bool isWin) {

    if(isWin) printf("Da\n");
    else printf("Nu\n");

    int iPos, fPos; //pozitia finala a unui ciclu, respectiv cea finala

    for(int i = 1; i <= numberOfCycles; i += 2) {

        iPos = positions[i];
        fPos = positions[i + 1]; // numberOfCycles e numar par, deci nu ies din vector

        for(int j = iPos; j <= fPos; j++)
            printf("%d ", cycles[j]);
        
        printf("\n");

    }
}