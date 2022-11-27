#include <stdio.h>
#include <string.h>

//scot un primul cuvant
char *next (char *from, char *word);

int main() {

    char text[101], result[101];

    //citirea
    fgets(text, 101, stdin);

    text[strlen(text) - 1] = '\0';

    //las in /**/ in caz se vrea outputul de la functia next, dar merge

    /*
    next(text, text);

    printf("Text: %s\n", text);
    */



    //reolvare fara next ca mi se pare mai usor

    int j = 0;

    for(int i = 0; i < strlen(text) - 1; i++) {

        //copiez literele mici in result, iar daca dau de ceva care nu e litera mica
        //pun un spatiu
        if(text[i] >= 'a' && text[i] <= 'z') {

                result[j++] = text[i];

                if(text[i + 1] < 'a' || text[i + 1] > 'z') result[j++] = ' ';

        } 

    }

    //verific si ultimul caracater din text daca trebuie adaugat
    if(text[strlen(text) - 1] >= 'a' && text[strlen(text) - 1] <= 'z') 
        result[j++] = text[strlen(text) - 1];

    result[j] = '\0';
    
    printf("%s", result);

    return 0;

}

//scot un primul cuvant
char *next (char *from, char *word) {

    int j = 0, i = 0;

    while(from[i] < 'a' || from[i] > 'z' && from[i] < strlen(from)) i++;

    //pun in word caracterele consecutive care sunt litere mici
    for( ; i < strlen(from) && from[i] >= 'a' && from[i] <= 'z'; i++) 
        word[j++] = from[i];

    word[j] = '\0';

    return word;    

}