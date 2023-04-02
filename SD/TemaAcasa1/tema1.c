/* NENCIU George-Robert - 313CC */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "operation.h"

int main() {

    FILE *src, *dest;
    dest = fopen("tema1.out", "w"); //golesc fisierul
    fclose(dest);

    char inputFile[100];
    const char* COMMANDS[] = {"MOVE_LEFT_CHAR", "MOVE_RIGHT_CHAR", "MOVE_LEFT",
                              "MOVE_RIGHT", "WRITE", "INSERT_LEFT",
                              "INSERT_RIGHT", "SHOW_CURRENT", "SHOW",
                              "UNDO", "REDO", "EXECUTE"};

    src = fopen("tema1.in", "r");
    fgets(inputFile, 100, src);
    int length = strlen(inputFile) - 1, i, j, n, pos, totalU, totalR;
    inputFile[length] = '\0'; //numarul de operatii care vor fi citite
    n = totalU = totalR = 0;  //totalU si totalR tin minte cate elemente au stivele

    for(i = 0; i < length; i++) n = n * 10 + inputFile[i] - '0'; //string catre int

    Queue *queueExec = initQueue();
    List *list = initLista();   //"banda magica"
    addNode(list, 1, '#');
    list->finger = list->head->next;    //capul nu se modifica
    Stack *stackUndo = initStack(), *stackRedo = initStack();

    for(i = 0; i < n; i++) {
        fgets(inputFile, 100, src);
        inputFile[strlen(inputFile) - 1] = '\0';

        for(j = 0; j < 12; j++) //caut a cata comanda e din lista
            if(strstr(inputFile, COMMANDS[j])) { pos = j + 1; break; }

        if(pos > 0 && pos < 8) enqueue(queueExec, inputFile);
        else if(pos == 8) showCurrent(list->finger);
        else if(pos == 9) show(list, list->finger);
        else if(pos == 10) list->finger = undo(stackUndo, stackRedo, list->finger, &totalU, &totalR);
        else if(pos == 11) list->finger = redo(stackUndo, stackRedo, list->finger, &totalU, &totalR);
        else if(pos == 12) list->finger = execute(queueExec, list->finger, &stackUndo, &stackRedo, list, &totalU, &totalR);
    }
    freeQueue(queueExec); //eliberarea memoriei
    freeStack(stackUndo, totalU);
    freeStack(stackRedo, totalR);
    freeList(list);
    fclose(src);
    return 0;
}