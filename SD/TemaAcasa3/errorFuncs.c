/* NENCIU George-Robert - 313CC */
#include "errorFuncs.h"

void sendErrorOfFileNull(const char *name, const  char *type, const char *funcName) {
    char errMes[8][100] = {"Couldn't open file '",
                           "_name_to_be_inserted_",
                           "' (type: '",
                           "_type_to_be_inserted_", "') ",
                           "because after calling it in function '",
                           "_function_name_to_be_inserted_",
                           "' the returned value is NULL.\n"};

    //adaug informatia necesara
    strcpy(errMes[1], name);
    strcpy(errMes[3], type);
    strcpy(errMes[6], funcName);
    int i;
    char toSend[50];
    strcpy(toSend, errMes[0]);
    for(i = 1; i < 8; i++) strcat(toSend, errMes[i]); //formez mesajul
    fprintf(stderr, "%s", toSend);
    exit(1);
}

void sendErrorOfNull(const char *name, const  char *type, const char *funcName) {
    char errMes[8][100] = {"Couldn't alloc memory to pointer '",
                           "_name_to_be_inserted_",
                           "' (type: '",
                           "_type_to_be_inserted_", "') ",
                           "because after calloc in function '",
                           "_function_name_to_be_inserted_",
                           "' the returned value is NULL.\n"};

    //adaug informatia necesara
    strcpy(errMes[1], name);
    strcpy(errMes[3], type);
    strcpy(errMes[6], funcName);
    int i;
    char toSend[50];
    strcpy(toSend, errMes[0]);
    for(i = 1; i < 8; i++) strcat(toSend, errMes[i]); //formez mesajul
    fprintf(stderr, "%s", toSend);
    exit(1);
}