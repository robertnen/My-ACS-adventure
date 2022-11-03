#ifndef MYHEADER_H_
#define MYHEADER_H_

typedef enum {false = 0, true = 1} bool; //bool_t


                    // ---- Citire / scriere pentru vectori / matrici  ---- //


    //Citeste un vector de tip int si salveaza marimea
    //*Functia NU modifica marimea vectorului...
    void readVector(int** vector, int size);

    //Citeste un vector de tip float si salveaza marimea
    //*Functia NU modifica marimea vectorului...
    void readVectorF(float** vector, int size);

    //Afiseaza o secventa a vectorului incepand de la pos1 pana la pos2 (inclusiv).
    void showVector(int* vector, int pos1, int pos2);

    //Citeste o matrice.
    //*Functia NU modifica numarul de linii si de coloane...
    void readMatrix(int*** matrix, int row, int col);

    //Afiseaza o matrice.
    void showMatrix(int** matrix, int row, int col);


                    // ---- Diverse  ---- //


    //Face ca vectorul sa aiba toate elementele 0.
    void nullVector(int** vector, int size);

    //Elibereaza spatiul alocat pentru o matrice.
    //Are nevoie de numarul de linii...
    void freeMatrix(int*** matrix, int numberOfLines);


                    // ---- Sortari  ---- //


    //Sorteaza un vector de tip int crescator de la pos1 pana la pos2 inclusiv.
    void sortVector(int** vector, int pos1, int pos2);

    //Sorteaza un vector de tip float crescator de la pos1 pana la pos2 inclusiv.
    void sortVectorF(float** vector, int pos1, int pos2);

    //Sorteaza un vector de tip int descrescator de la pos1 pana la pos2 inclusiv.
    void reversedSortVector(int** vector, int pos1, int pos2);

    //Sorteaza un vector de tip float descrescator de la pos1 pana la pos2 inclusiv.
    void reversedSortVectorF(float** vector, int pos1, int pos2);


                    // ---- Verificare de proprietati a unui vector  ---- //


    //Verifica daca un vector e ordonat crescator.
    bool isAscendedOrdered(int* vector, int size);

    //Verifica daca un vector e ordonat descrescator.
    bool isDescendedOrdered(int* vector, int size);

    //Verifica daca un vector e constant.
    bool isConstant(int* vector, int size);


                    // ---- Implementarea  ---- //



                    // ---- Citire / scriere pentru vectori / matrici  ---- //


    //Citeste un vector de tip int si salveaza marimea
    //*Functia NU modifica marimea vectorului...
    void readVector(int** vector, int size) {

            (*vector) = (int*) malloc(size * sizeof(int));

            for(int i = 0; i < size; i++)
                scanf("%d", &(*vector)[i]);
    }

    //Citeste un vector de tip float si salveaza marimea
    //*Functia NU modifica marimea vectorului...
    void readVectorF(float** vector, int size) {

            (*vector) = (float*) malloc(size * sizeof(float));

            for(int i = 0; i < size; i++)
                scanf("%f", &(*vector)[i]);
    }

    //Afiseaza o secventa a vectorului incepand de la pos1 pana la pos2 (inclusiv).
    void showVector(int* vector, int pos1, int pos2) {

        for(int i = pos1; i <= pos2; i++)
            printf("%d ", vector[i]);

    }    

    //Citeste o matrice.
    //*Functia NU modifica numarul de linii si de coloane...
    void readMatrix(int*** matrix, int row, int col) {

        (*matrix) = (int**) malloc(row * sizeof(int*));
    
        for(int i = 0; i < row; i++) {

            (*matrix)[i] = (int*) malloc(col * sizeof(int));

            for(int j = 0; j < col; j++) 
                scanf("%d", &(*matrix)[i][j]);
        
        }
    }

    //Afiseaza o matrice.
    void showMatrix(int** matrix, int row, int col) {

        for(int i = 0; i < row; i++) {

            for(int j = 0; j < col; j++)
                printf("%d ", matrix[i][j]);
        
            printf("\n");
        }
    }


                    // ---- Diverse  ---- //


    //Face ca vectorul sa aiba toate elementele 0.
    void nullVector(int** vector, int size) {

        for(int i = 0; i < size; i++)
            (*vector)[i] = 0;
    }

    //Elibereaza spatiul alocat pentru o matrice.
    //Are nevoie de numarul de linii...
    void freeMatrix(int*** matrix, int numberOfLines) {

        for(int i = 0; i < numberOfLines; i++)
            free((*matrix)[i]);
        free((*matrix));
    }


                    // ---- Sortari  ---- //


    //Sorteaza un vector de tip int crescator de la pos1 pana la pos2 inclusiv.
    void sortVector(int** vector, int pos1, int pos2) {

        bool isOrdered = false;
        int aux;

        while(!isOrdered) {

            isOrdered = true;

            for(int i = pos1; i < pos2; i++) 
                if((*vector)[i] > (*vector)[i + 1]) {

                    isOrdered = false;

                    //swap
                    aux = (*vector)[i];
                    (*vector)[i] = (*vector)[i + 1];
                    (*vector)[i + 1] = aux;

                }      
        }
    }

    //Sorteaza un vector de tip float crescator de la pos1 pana la pos2 inclusiv.
    void sortVectorF(float** vector, int pos1, int pos2) {

        bool isOrdered = false;
        float aux;

        while(!isOrdered) {

            isOrdered = true;

            for(int i = pos1; i < pos2; i++) 
                if((*vector)[i] > (*vector)[i + 1]) {

                    isOrdered = false;

                    //swap
                    aux = (*vector)[i];
                    (*vector)[i] = (*vector)[i + 1];
                    (*vector)[i + 1] = aux;

                }      
        }
    }

    //Sorteaza un vector descrescator de la pos1 pana la pos2 inclusiv.
    void reversedSortVector(int** vector, int pos1, int pos2) {

        bool isOrdered = false;
        int aux;

        while(!isOrdered) {

            isOrdered = true;

            for(int i = pos1; i < pos2; i++) 
                if((*vector)[i] < (*vector)[i + 1]) {

                    isOrdered = false;

                    //swap
                    aux = (*vector)[i];
                    (*vector)[i] = (*vector)[i + 1];
                    (*vector)[i + 1] = aux;

                }      
        }
    }


                    // ---- Verificare de proprietati a unui vector  ---- //


    //Sorteaza un vector de tip float descrescator de la pos1 pana la pos2 inclusiv.
    void reversedSortVectorF(float** vector, int pos1, int pos2) {

        bool isOrdered = false;
        float aux;

        while(!isOrdered) {

            isOrdered = true;

            for(int i = pos1; i < pos2; i++) 
                if((*vector)[i] < (*vector)[i + 1]) {

                    isOrdered = false;

                    //swap
                    aux = (*vector)[i];
                    (*vector)[i] = (*vector)[i + 1];
                    (*vector)[i + 1] = aux;

                }      
        }
    }

    //Verifica daca un vector e ordonat crescator.
    bool isAscendedOrdered(int* vector, int size) {

        for(int i = 0; i < size - 1; i++)
            if(vector[i] > vector[i + 1]) return false;

        return true;
    }

    //Verifica daca un vector e ordonat descrescator.
    bool isDescendedOrdered(int* vector, int size) {

        for(int i = 0; i < size - 1; i++)
            if(vector[i] < vector[i + 1]) return false;

        return true;
    }

    //Verifica daca un vector e constant.
    bool isConstant(int* vector, int size) {

        for(int i = 0; i < size - 1; i++)
            if(vector[i] != vector[i + 1]) return false;

        return true;
    }

#endif